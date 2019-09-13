/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:17:53 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/11 20:17:55 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "surface_manipulation.h"

t_rect		create_rect(int x, int y, int width, int height)
{
	t_rect	rect;

	rect.pos.x = x;
	rect.pos.y = y;
	rect.width = width;
	rect.height = height;
	return (rect);
}

void		draw_rect(SDL_Surface *surface, t_rect *rect, Uint32 color)
{
	t_segment	s1;
	t_segment	s2;

	s1 = create_segment(rect->pos.x, rect->pos.y,
			rect->pos.x + rect->width, rect->pos.y);
	s2 = create_segment(rect->pos.x, rect->pos.y,
			rect->pos.x, rect->pos.y + rect->height);
	draw_segment(surface, s1, color);
	draw_segment(surface, s2, color);
	move_segment_at(&s1, rect->pos.x, rect->pos.y + rect->height);
	move_segment_at(&s2, rect->pos.x + rect->width - 1, rect->pos.y);
	draw_segment(surface, s1, color);
	draw_segment(surface, s2, color);
}

void		fill_rect(SDL_Surface *surface, t_rect *rect, Uint32 color,
				enum e_bool alpha)
{
	int	x;
	int	y;

	y = rect->pos.y + 1;
	while (y < rect->pos.y + rect->height)
	{
		x = rect->pos.x + 1;
		while (x < rect->pos.x + rect->width - 1)
		{
			if (x >= 0 && x < surface->w && y >= 0 && y < surface->h)
			{
				if (alpha)
					put_pixel_alpha(surface, x, y, color);
				else
					put_pixel(surface, x, y, color);
			}
			x++;
		}
		y++;
	}
}

enum e_bool	is_in_rect(t_rect *rect, int x, int y)
{
	if (x >= rect->pos.x && x <= rect->pos.x + rect->width
		&& y >= rect->pos.y && y <= rect->pos.y + rect->height)
		return (e_true);
	return (e_false);
}
