/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:17:16 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/07 22:40:19 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	isXWall(t_data *data, int input)
{
	int	x;
	int	y;
	int	wall;

	x = (data->minimap->cursor_x - MINIMAP_SIZE / 15) / data->minimap->squareSize;
	y = (data->minimap->cursor_y - MINIMAP_SIZE / 15) / data->minimap->squareSize;
	wall = 0;
	printf("%d [%d] = %d\n", data->minimap->cursor_x, x + 1, data->map->map[y][x + 1]);
	if (input == D)
	{
		if (data->map->map[y][x + 1] == WALL)
			printf("%d * %d + %d = %d\n", x , data->minimap->squareSize ,MINIMAP_SIZE / 15,x * data->minimap->squareSize + MINIMAP_SIZE / 15);
		if (data->map->map[y][x + 1] == WALL)
			wall = x * data->minimap->squareSize + MINIMAP_SIZE / 15 + data->minimap->squareSize / 2;
		else
			wall = data->minimap->cursor_x + STEP;
		
	}
	else if (input == A)
	{
		if (data->map->map[y][x - 1] == WALL)
			wall = x * data->minimap->squareSize + MINIMAP_SIZE / 15;
		else
			wall = data->minimap->cursor_x - STEP;
	}
	data->minimap->cursor_x -= data->minimap->cursor_x - wall;
}

void	isYWall(t_data *data, int input)
{
	int	x;
	int	y;
	int	wall;

	x = (data->minimap->cursor_x - MINIMAP_SIZE / 15) / data->minimap->squareSize;
	y = (data->minimap->cursor_y - MINIMAP_SIZE / 15) / data->minimap->squareSize;
	wall = 0;
	printf("[%d] = %d\n", y + 1, data->map->map[y + 1][x]);
	if (input == W)
	{
		if (data->map->map[y + 1][x] == WALL)
			wall = y * data->minimap->squareSize + MINIMAP_SIZE / 15;
		else
			wall = data->minimap->cursor_y - STEP;
	}
	else if (input == S)
	{
		if (data->map->map[y - 1][x] == WALL)
			wall = y * data->minimap->squareSize + MINIMAP_SIZE / 15;
		else
			wall = data->minimap->cursor_y + STEP;
	}
	data->minimap->cursor_y -= data->minimap->cursor_y - wall;
}

void	pixelPutCursor(t_image *cursor, int color, int size, int radius)
{
	char	*pxl;
	int		x;
	int		y;
	int		dx;
	int		dy;

	y = 0;
	while (y < size)
	{//TODO faire la meme couleur a chque fois ptet et faire degrade
		x = 0;
		while (x < size)
		{
			dx = x - radius;
			dy = y - radius;
			if (dx * dx + dy * dy <= radius * radius)
			{
				pxl = cursor->adress +
					(y * cursor->l_len + x * (cursor->bpp / 8));
				*(unsigned int *)pxl = color;
			}
			x++;
		}
		y++;
	}
}
