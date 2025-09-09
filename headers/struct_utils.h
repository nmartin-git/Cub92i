/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:52:00 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/09 21:44:05 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_UTILS_H
# define STRUCT_UTILS_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "parsing.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_crosshair	t_crosshair;

typedef enum e_face
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}							t_face;

typedef struct s_image
{
	void					*image;
	char					*adress;
	int						bpp;
	int						l_len;
	int						tab_x;
	int						tab_y;
}							t_image;

typedef struct s_minimap
{
	void					*display;
	t_image					*minimap;
	t_image					*cursor;
	t_image					*direction;
	t_image					*raycasting;
	float					p_angle;
	float					cursor_x;
	float					cursor_y;
	int						pxl_size;
	int						p_color;
	int						w_color;
	int						f_color;
	int						b_color;
	int						c_color;
	int						x;
	int						y;
	int						sb15; //minimap_size_by_15
	float					scale;
}							t_minimap;

typedef struct s_pos
{
	int						x;
	int						y;
}							t_pos;

typedef struct s_ray
{
	int						x_y;
	float					angle;
	long					dst;
	int						percent;
	int						door;
}							t_ray;

typedef struct s_data
{
	void					*display;
	void					*window;
	t_image					*background;
	t_image					*image;
	t_image					*pv;
	int						health;
	int						puff;
	t_map					*map;
	t_minimap				*mmap; //minimap
	t_minimap				*sc_mmap; //screen_minimap
	t_minimap				*raycast;
	t_image					*texture_n;
	t_image					*texture_s;
	t_image					*texture_e;
	t_image					*texture_w;
	t_image					*texture_door;
	t_crosshair				*crosshair;
	int						keys[10];
	int						scale;
}							t_data;

t_image						*new_image(void *display, int tab_x, int tab_y);
void						free_image(t_image *image, void *display);

#endif