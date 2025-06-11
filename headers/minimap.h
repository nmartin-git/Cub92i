/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:23:42 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/11 15:30:19 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "struct_utils.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# define EMPTY_COLOR 0
# define MINIMAP_SIZE 400
# define WALL 1
# define FLOOR 0
# define EMPTY 8
# define STEP 3
# define DIRECTION 0.1
# define PI 3.1415926535
# define FOV 60

enum input
{
	W,
	A,
	S,
	D
};

/*---minimap.c---*/
void	setMinimapColor(t_minimap *minimap);
int		getMinimapColor(t_minimap *minimap, int content);
void	minimapData(t_minimap *minimap, t_data *data);
void	pixelPutSquare(t_minimap *minimap, t_pos pixel, int color);
void	minimapCreate(t_minimap *minimap, int **map);

/*---cursor.c---*/
void	isXWall(t_data *data, int input);
void	isYWall(t_data *data, int input);
void	putCursorDirection(t_minimap *minimap);
void	pixelPutCursor(t_image *cursor, int color, int size, int radius);

/*---raycasting.c---*/
void	pixel_put(t_image *raycasting, t_pos pixel, int color);
void	small_angle(t_image *raycasting, t_pos pixel, int dx, int dy);
void	big_angle(t_image *raycasting, t_pos pixel, int dx, int dy);
void	putRaycasting(t_minimap *minimap, double fov);

#endif