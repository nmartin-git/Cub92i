/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:52:00 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/19 12:34:28 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_UTILS_H
# define STRUCT_UTILS_H

# include "parsing.h"
# include <unistd.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>

typedef struct s_image
{
	void		*image;
	char		*adress;
	int			bpp;
	int			l_len;
	int			tab_x;
	int			tab_y;
}	t_image;

typedef struct s_minimap
{
	void	*display;
	t_image	*minimap;
	t_image	*cursor;
	t_image	*direction;
	t_image	*raycasting;
	double	p_angle;
	int		cursor_x;
	int		cursor_y;
	int		pxl_size;
	int		p_color;
	int		w_color;
	int		f_color;
	int		b_color;
	int		c_color;
	int		x;
	int		y;
	t_ennemy	*ennemies;
}	t_minimap;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_ray
{
	int		x_y;
	double	angle;
	long	dst;
	int		percent;
}	t_ray;

typedef struct s_data
{
	void		*display;
	void		*window;
	t_image		*image;
	t_image		*pv;
	int			health;
	int			puff;
	t_map		*map;
	t_minimap	*minimap;
	t_minimap	*raycast;
}	t_data;

typedef struct s_ennemy
{
	t_image		*s_ennemy;
	int			pos_x;
	int			pos_y;
	t_ennemy	*next;
}	t_ennemy;

t_image	*new_image(void *display, int tab_x, int tab_y);
void	free_image(t_image *image, void *display);

#endif