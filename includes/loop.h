/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 06:11:39 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 06:13:37 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOP_H
# define LOOP_H

# include "doom.h"
# include "map.h"
# include <SDL.h>
# include "timer_handler.h"

typedef struct			s_logic_params
{
	t_env				*e;
	t_map				*map;
	const Uint8			*state;
	t_timer_handler		*timer_handler;
	enum e_bool			*stop;
}						t_logic_params;

typedef struct			s_frame_event_params
{
	t_env				*e;
	t_map				*map;
	double				time;
	int					fps;
}						t_frame_event_params;

void					key_handler(const Uint8 *state, t_player *p,
							t_timer_handler *timer_handler);
enum e_bool				frame_event(double ms_since_update, t_params params);
t_frame_event_params	frame_event_params_init(t_env *e);
t_logic_params			logic_params_init(t_env *e, const Uint8 *state,
							t_timer_handler *timer_handler, enum e_bool *stop);
enum e_bool				update_logic(double ms_since_update, t_params params);
void					loop_events(t_env *e, const Uint8 *state,
							t_timer_handler *timer_handler, enum e_bool *stop);
void					update_enemies(t_sectors *sectors, t_coords camera_pos);

#endif
