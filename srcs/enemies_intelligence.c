/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_intelligence.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 07:23:58 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 07:24:00 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "horizontal_motion.h"
#include "default.h"
#include "player.h"
#include "enemies_intelligence.h"
#include "doom.h"
#include "enemies.h"
#include "utils.h"
#include "in_which_sector.h"

void		enemy_move(t_enemy *enemy, t_sector *enemy_sector, t_env *e,
				double ms_since_update)
{
	t_vector			direction;
	t_linked_enemies	*extracted_n;
	t_sector			*new_sector;
	t_coords			new_position;

	(void)e;
	direction = (t_vector){enemy->heading.x * enemy->speed * MS_TO_S
						* ms_since_update, enemy->heading.y
						* enemy->speed * MS_TO_S * ms_since_update};
	new_sector = enemy_sector;
	new_position = allowed_move(direction,
			(t_coords){enemy->object->x, enemy->object->y}, &new_sector);
	if (!new_sector)
		return ;
	enemy->object->x = new_position.x;
	enemy->object->y = new_position.y;
	if (new_sector != enemy_sector)
	{
		extracted_n = extract_enemy(&enemy_sector->enemies, enemy);
		add_enemy(&new_sector->enemies, extracted_n);
	}
}

void		boss_intelligence(t_enemy *enemy, t_sector *enemy_sector, t_env *e,
				double ms_since_update)
{
	double		distance;
	double		ratio;
	t_vector	to_player;

	distance = get_distance_between_points(e->p.pos.x, e->p.pos.y,
			enemy->object->x, enemy->object->y);
	ratio = distance / 2;
	e->p.health -= BLACKHOLE_AURA_DAMAGE / 60.0 / ratio;
	if (e->p.health <= 0)
		e->p.dead = e_true;
	e->p.hurt = ratio <= 2.5;
	to_player = (t_vector){e->p.pos.x - enemy->object->x,
						e->p.pos.y - enemy->object->y};
	normalize_vector(&to_player);
	enemy->heading = to_player;
	enemy_move(enemy, enemy_sector, e, ms_since_update);
	enemy->object->z += 0.005 * cos(enemy->animation_time / 1000.);
}

enum e_bool	let_enemies_act(double ms_since_update, t_params params)
{
	t_env				*e;
	t_enemy				*enemy;
	int					i;
	t_linked_enemies	*n;
	t_sector			*sector;

	if (ms_since_update > 10000)
		return (e_true);
	e = (t_env *)params;
	i = 0;
	while (i < e->map->sectors->count)
	{
		sector = e->map->sectors->items[i];
		n = sector->enemies;
		while (n)
		{
			enemy = &n->item;
			if (enemy->time_in_death <= 0)
				enemy->act(enemy, sector, e, ms_since_update);
			enemy->animation_time += ms_since_update;
			n = n->next;
		}
		i++;
	}
	return (e_true);
}
