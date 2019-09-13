/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 02:34:54 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 19:47:39 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <pthread.h>
# include <SDL_mixer.h>
# include "libft.h"
# include "struct_sdl.h"
# include "e_bool.h"
# include "player.h"
# include "config.h"
# include "fonts.h"
# include "textures.h"
# include "sounds.h"

typedef struct			s_env
{
	t_config			op;
	t_player			p;
	t_sdl				doom;
	t_map				*map;
	Mix_Music			*music;
	t_fonts				*fonts;
	t_textures			*textures;
	t_sounds			*sounds;
	t_timer_handler		timer_handler;
	pthread_t			blackhole_thread;
	char				*blackhole_buffer;
	enum e_bool			blackhole_thread_stop;
}						t_env;

void					error_doom(char *err);
void					quit_doom(t_env *e);
void					game_over(t_env *e, TTF_Font *font,
							SDL_Surface *surface, t_config *op);
void					game_victory(TTF_Font *font,
							SDL_Surface *surface, t_config *op);
void					loop_doom(t_env *e);

#endif
