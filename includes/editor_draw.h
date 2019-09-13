/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 04:41:56 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 04:43:19 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_DRAW_H
# define EDITOR_DRAW_H

# include "map.h"
# include "struct_sdl.h"
# include "editor.h"

typedef struct s_editor	t_editor;
typedef struct s_buttons	t_buttons;

# define DRAW_MAP_X EDIT_W_H / 3
# define DRAW_MAP_Y EDIT_H_H

# define WHITE 0xFFFFFFFF
# define RED 0xFFFF0000
# define ENEMY_COLOR 0xFFFFAAAA
# define OBJECT_COLOR 0xFFF49242
# define GREEN 0xFF00FF00
# define BLUE 0xFF0000FF
# define L_BLUE 0xFF8888FF
# define YELLOW 0xFFF4EE42
# define BACKGROUND_COLOR 0xFF756F68
# define YELLOW 0xFFF4EE42
# define PLAYER_COLOR WHITE
# define PICKABLE_COLOR 0xFFC68FF7

void	show_possible_new_sector(t_editor *ed, int x, int y);
void	draw_background(t_editor *ed);
void	draw_panel_back(SDL_Surface *surface);
void	draw_editor(t_editor *ed);
void	draw_panel(t_editor *ed);
void	draw_corners_editor(SDL_Surface *surface, t_segment *s);
void	draw_walls_editor(SDL_Surface *surface, t_walls *walls,
			t_i_coords map_offset, int zoom);
void	draw_enemies_in_sector_editor(SDL_Surface *target,
		t_linked_enemies *enemies, t_i_coords map_offset, int zoom);
void	draw_objects_in_sector_editor(SDL_Surface *target, t_objects *objects,
			t_i_coords map_offset, int zoom);
void	draw_pickables_in_sector_editor(SDL_Surface *target,
		t_pickables *pickables, t_i_coords map_offset, int zoom);
void	highlight_selected_wall(t_editor *ed);

#endif
