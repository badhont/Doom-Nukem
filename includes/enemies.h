/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 05:06:42 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 05:20:02 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMIES_H
# define ENEMIES_H

# include "SDL.h"

# include "textures.h"
# include "utils.h"
# include "objects.h"
# include "e_bool.h"
# include "timer_handler.h"
# include "sectors.h"
# include "enemies_intelligence.h"

# define BASE_SCOOTER_SPEED 1
# define FAST_SCOOTER_SPEED 5
# define BASE_BLACKHOLE_SPEED 0.5
# define BRAZILIAN_HANDGUN_DAMAGE 2

typedef struct s_object	t_object;

typedef struct				s_enemy
{
	t_object				*object;
	int						life_remaining;
	double					death_duration;
	double					time_in_death;
	enum e_bool				to_destroy;
	t_vector				heading;
	SDL_Surface				*front;
	SDL_Surface				*left;
	SDL_Surface				*right;
	SDL_Surface				*back;
	enum					e_enemy_type
	{
		et_boss,
		et_brazil
	}						type;
	t_enemy_intelligence	act;
	double					speed;
	SDL_Surface				*explosion[16];
	double					animation_time;
	int						step;
}							t_enemy;

typedef struct				s_linked_enemies
{
	t_enemy					item;
	struct s_linked_enemies	*next;
}							t_linked_enemies;

void						free_enemies(t_linked_enemies *enemies);
void						read_enemies_from_file(
							int fd,
							t_textures *textures,
							t_linked_enemies **enemies);
void						write_enemies_to_file(int fd,
								t_linked_enemies *enemies);

void						read_enemy_from_file(int fd,
								t_textures *textures, t_enemy *enemy);
void						write_enemy_to_file(int fd, t_enemy enemy);

void						dmg_enemy(t_env *e,
								t_timer_handler *timer_handler,
								t_enemy *enemy, Uint32 damage);
void						add_enemy(t_linked_enemies **linked_enemies,
								t_linked_enemies *enemy);
t_linked_enemies			*extract_enemy(t_linked_enemies **linked_enemies,
								t_enemy *enemy);
void						delete_enemy(t_linked_enemies **linked_enemies,
								t_enemy *enemy);

t_linked_enemies			*add_new_enemy_to_sector_at_pos(t_sector *sector,
								t_coords pos, t_textures *textures);
t_enemy						create_default_enemy(t_textures *textures);

#endif
