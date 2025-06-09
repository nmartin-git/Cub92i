/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:23:42 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/09 15:46:18 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "struct_utils.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# define MINIMAP_SIZE 1800
# define WALL 1
# define FLOOR 0
# define EMPTY 8
# define STEP 10

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
void	pixelPutCursor(t_image *cursor, int color, int size, int radius);

#endif