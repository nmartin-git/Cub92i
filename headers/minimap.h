/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:23:42 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/06 17:57:03 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "struct_utils.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# define MINIMAP_SIZE 400
# define CURSOR_RADIUS 140
# define WALL 1
# define FLOOR 0
# define EMPTY 8

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

/*---minimap.c---*/
void	setMinimapColor(t_minimap *minimap);
int		getMinimapColor(t_minimap *minimap, int content);
void	minimapData(t_minimap *minimap, void *display, int x, int y);
void	pixelPutSquare(t_minimap *minimap, t_pos pixel, int color);
void	minimapCreate(t_minimap *minimap, int **map);

/*---cursor.c---*/
void	pixelPutCursor(t_image *cursor, int color, int width, int height);

#endif