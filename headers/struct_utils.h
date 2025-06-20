/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:52:00 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/07 16:34:27 by nmartin          ###   ########.fr       */
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
}	t_image;

typedef struct s_minimap
{
	void	*display;
	t_image	*minimap;
	t_image	*cursor;
	int		cursor_x;
	int		cursor_y;
	int		squareSize;
	int		p_color;
	int		w_color;
	int		f_color;
	int		b_color;
	int		c_color;
	int		x;
	int		y;
	int		tab_x;
	int		tab_y;
}	t_minimap;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_data
{
	void		*display;
	void		*window;
	t_image		*image;
	t_map		*map;
	t_minimap	*minimap;
}	t_data;

t_image	*newImage(void *display, int tab_x, int tab_y);
void	freeImage(t_image *image, void *display);

#endif