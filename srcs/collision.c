/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 06:41:37 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 06:41:41 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "default.h"

static void			find_objects_collisions_in_sector(t_sector *sector,
						t_segment *ray, t_collisions **collisions)
{
	int				i;
	t_coords		inters;
	double			distance;
	t_segment		s;
	t_collisions	*new;

	i = 0;
	while (i < sector->objects->count)
	{
		s = perpendicular_segment_from_point(
				sector->objects->items + i,
				ray->x1,
				ray->y1);
		if (segments_intersect(ray, &s, &inters))
		{
			distance = get_distance_between_points(ray->x1, ray->y1, inters.x,
					inters.y);
			new = insert_collision(collisions, distance, inters);
			new->item.type = ct_object;
			new->item.d.object = sector->objects->items + i;
			new->item.object_segment = s;
		}
		i++;
	}
}

static void			find_lever_collisions(t_collisions **collisions,
						t_wall *wall, double distance, t_coords inters)
{
	t_lever			*lever;
	double			offset_on_wall;
	t_collisions	*new;

	if (distance < PLAYER_THICKNESS)
		return ;
	if (!(lever = wall->lever) || lever->wall_object == NULL)
		return ;
	offset_on_wall = get_distance_between_points(wall->segment.x1,
			wall->segment.y1, inters.x, inters.y);
	if (offset_on_wall < wall->lever->wall_object->offset_on_wall
		|| offset_on_wall >= lever->wall_object->offset_on_wall
			+ lever->wall_object->size)
		return ;
	new = add_collision(collisions, distance, inters);
	new->item.type = ct_lever;
	new->item.d.lever = lever;
}

static enum e_bool	check_best_collision(t_collisions **collisions,
						t_collision best_collision)
{
	t_collisions	*new;

	if (best_collision.distance >= HORIZON)
		return (e_false);
	if (best_collision.d.wall->type == e_wall)
		new = insert_collision(collisions, best_collision.distance,
			best_collision.inters);
	else
		new = add_collision(collisions, best_collision.distance,
			best_collision.inters);
	new->item.type = ct_wall;
	new->item.d.wall = best_collision.d.wall;
	if (new->item.d.wall->type == e_wall)
	{
		free_collisions(new->next);
		new->next = NULL;
	}
	return (e_true);
}

static enum e_bool	find_wall_collisions_in_sector(t_sector *sector,
						t_segment *ray, t_collisions **col,
						t_wall *last_portal)
{
	int				i;
	t_coords		in;
	double			dist;
	t_collision		b_col;

	i = -1;
	b_col.distance = HORIZON;
	while (++i < sector->walls->count)
	{
		if (last_portal == sector->walls->items[i])
			continue ;
		if (segments_intersect(ray, &sector->walls->items[i]->segment, &in))
		{
			dist = get_distance_between_points(ray->x1, ray->y1, in.x, in.y);
			if (dist < b_col.distance)
			{
				b_col.distance = dist;
				b_col.inters = in;
				b_col.d.wall = sector->walls->items[i];
			}
			find_lever_collisions(col, sector->walls->items[i], dist, in);
		}
	}
	return (!check_best_collision(col, b_col)) ? e_false : e_true;
}

void				find_ray_collisions(t_sector *sector, t_segment *ray,
						t_collisions **collisions)
{
	t_wall			*last_portal;
	t_collisions	**node;

	last_portal = NULL;
	*collisions = NULL;
	node = collisions;
	while (1)
	{
		find_enemies_collisions_in_sector(sector, ray, node);
		find_objects_collisions_in_sector(sector, ray, node);
		find_pickables_collisions_in_sector(sector, ray, node);
		if (!find_wall_collisions_in_sector(sector, ray, node, last_portal))
			break ;
		while ((*node)->next)
			node = &(*node)->next;
		if ((*node)->item.d.wall->type == e_wall
			|| (*node)->item.d.wall->to_infinity)
			break ;
		last_portal = (*node)->item.d.wall;
		sector = get_next_sector_addr(sector, (*node)->item.d.wall);
		node = &(*node)->next;
	}
}
