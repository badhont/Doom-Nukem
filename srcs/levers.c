/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:34:23 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 11:34:26 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "levers.h"
#include "serialisation.h"
#include "doom.h"
#include "default.h"
#include "walls.h"
#include "collision.h"

static void	use_lever(t_lever *lever, t_timer_handler *timer_handler)
{
	t_door_animation	*animation;

	if (lever->activated)
		return ;
	lever->activated = e_true;
	lever->wall_object->texture = lever->down_texture;
	if (!(animation = (t_door_animation *)malloc(sizeof(t_door_animation))))
		error_doom("can't allocate animation");
	animation->elapsed_time = 0;
	animation->total_time = 2000;
	animation->door = lever->door;
	animation->target_offset = get_distance_between_points(
			lever->door->segment.x1, lever->door->segment.y1,
			lever->door->segment.x2, lever->door->segment.y2);
	add_event(timer_handler, 10, &animate_door, animation);
}

void		use_lever_if_available(t_player *p, t_timer_handler *timer_handler)
{
	t_segment		ray;
	t_collisions	*collisions;
	t_collisions	*n;

	ray = create_segment(p->pos.x, p->pos.y,
			p->pos.x + 2 * PLAYER_THICKNESS * cos(p->heading),
			p->pos.y - 2 * PLAYER_THICKNESS * sin(p->heading));
	find_ray_collisions(p->current_sector, &ray, &collisions);
	n = collisions;
	while (n)
	{
		if (n->item.type == ct_lever)
			use_lever(n->item.d.lever, timer_handler);
		n = n->next;
	}
	free_collisions(collisions);
}

void		create_lever(t_wall *wall, t_wall *target, t_textures *textures)
{
	t_lever	*lever;

	if (!(lever = (t_lever *)malloc(sizeof(t_lever))))
		error_doom("Couldn't allocate new lever");
	lever->activated = e_false;
	lever->door = target;
	find_texture_by_name(textures, "textures/wall_objects/lever_up.bmp",
			&lever->up_texture);
	find_texture_by_name(textures, "textures/wall_objects/lever_down.bmp",
			&lever->down_texture);
	lever->wall_object = create_wall_object(textures);
	lever->wall_object->texture = lever->up_texture;
	wall->lever = lever;
}

void		read_lever_from_file(int fd, t_textures *textures, t_lever **lever)
{
	enum e_bool	wall_has_lever;

	if (read(fd, &wall_has_lever, sizeof(wall_has_lever)) <= 0)
		error_doom("can't read wall_has_lever");
	*lever = NULL;
	if (!wall_has_lever)
		return ;
	if (!(*lever = (t_lever *)malloc(sizeof(t_lever))))
		error_doom("cannot allocate t_lever");
	(*lever)->activated = e_false;
	read_wall_object_from_file(fd, textures, &(*lever)->wall_object);
	find_texture_from_file(fd, textures, &(*lever)->up_texture);
	find_texture_from_file(fd, textures, &(*lever)->down_texture);
	if (read(fd, &(*lever)->door_index, sizeof((*lever)->door_index)) <= 0)
		error_doom("rip door_index");
	(*lever)->door = NULL;
}

void		write_lever_to_file(int fd, t_linked_walls *linked_walls,
				t_lever *lever)
{
	enum e_bool	wall_has_lever;
	int			door_index;

	wall_has_lever = lever != NULL;
	if (write(fd, &wall_has_lever, sizeof(wall_has_lever)) <= 0)
		error_doom("can't write wall_has_lever");
	if (!wall_has_lever)
		return ;
	write_wall_object_to_file(fd, lever->wall_object);
	write_str_to_file(fd, lever->up_texture->userdata);
	write_str_to_file(fd, lever->down_texture->userdata);
	door_index = wall_index(linked_walls, lever->door);
	if (door_index < 0)
		error_doom("can't find door");
	if (write(fd, &door_index, sizeof(door_index)) <= 0)
		error_doom("can't write door index");
}
