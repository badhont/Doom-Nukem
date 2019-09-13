/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:25:37 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 20:45:26 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# include <SDL.h>

# define BITMAP_DEPTH 32

typedef struct				s_texture_node
{
	SDL_Surface				*texture;
	struct s_texture_node	*next;
}							t_texture_node;

typedef struct				s_textures
{
	t_texture_node			*first;
}							t_textures;

typedef struct				s_sdl_surface_info
{
	int						w;
	int						h;
	Uint8					depth;
	int						pitch;
	Uint32					rmask;
	Uint32					gmask;
	Uint32					bmask;
	Uint32					amask;
}							t_sdl_surface_info;

void						free_textures(t_textures *textures);
void						find_texture_by_name(t_textures *textures,
								char *name, SDL_Surface **texture);
void						add_bitmap_file_to_textures(t_textures *textures,
								char *path);

void						read_textures_from_file(int fd,
								t_textures **textures);
void						write_textures_to_file(int fd,
								t_textures *textures);

void						read_texture_node_from_file(int fd,
								t_texture_node **texture_node);
void						write_texture_node_to_file(int fd,
								t_texture_node *texture_node);

void						find_texture_from_file(int fd,
								t_textures *textures,
								SDL_Surface **surface);

void						add_texture(t_textures *textures,
								t_texture_node *new_node);

#endif
