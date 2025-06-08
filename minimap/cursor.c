/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:17:16 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/08 02:27:26 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

int get_pixel_color(t_image *image, int x, int y)
{
	char *dst = image->adress + (y * image->l_len + x * (image->bpp / 8));
	return *(unsigned int *)dst;
}

void	isXWall(t_data *data, int input)
{
	int	saved;
	int	x;
	int	y;

	saved = (data->minimap->cursor_x - MINIMAP_SIZE / 15) / data->minimap->squareSize;
	y = (data->minimap->cursor_y - MINIMAP_SIZE / 15) / data->minimap->squareSize;
	if (input == D)
	{
		x = (data->minimap->cursor_x + data->minimap->squareSize / 1.5 - MINIMAP_SIZE / 15 + STEP) / data->minimap->squareSize;
		if (data->map->map[y][x] == WALL)
		{
			data->minimap->cursor_x += (x * data->minimap->squareSize + MINIMAP_SIZE / 15) - (data->minimap->cursor_x + data->minimap->squareSize / 1.5);
			if (get_pixel_color(data->minimap->minimap, data->minimap->cursor_x + 1 - MINIMAP_SIZE / 15, data->minimap->cursor_y - MINIMAP_SIZE / 15) == data->minimap->f_color)
				data->minimap->cursor_x++;
		}
		else
			data->minimap->cursor_x += STEP;
		printf("-%d-\n", get_pixel_color(data->minimap->minimap, data->minimap->cursor_x + 1-MINIMAP_SIZE/15, data->minimap->cursor_y+15-MINIMAP_SIZE/15));
	}
	else if (input == A)
	{
		x = (data->minimap->cursor_x - MINIMAP_SIZE / 15 - STEP) / data->minimap->squareSize;
		printf("%d [%d] = %d\n", data->minimap->cursor_x, x, data->map->map[y][x]);
		if (data->map->map[y][x] == WALL)
			data->minimap->cursor_x -= data->minimap->cursor_x - (saved * data->minimap->squareSize + MINIMAP_SIZE / 15);
		else
			data->minimap->cursor_x -= STEP;
	}
}

void	isYWall(t_data *data, int input)
{
	int	x;
	int	y;

	x = (data->minimap->cursor_x - MINIMAP_SIZE / 15) / data->minimap->squareSize;
	y = (data->minimap->cursor_y - MINIMAP_SIZE / 15) / data->minimap->squareSize;
	printf("[%d] = %d\n", y + 1, data->map->map[y + 1][x]);
	if (input == W)
	{
		if (data->map->map[y + 1][x] == WALL)
			printf("%d * %d + %d = %d\n", y , data->minimap->squareSize ,MINIMAP_SIZE / 15,y * data->minimap->squareSize + MINIMAP_SIZE / 15);
		if (data->map->map[y + 1][x] == WALL)
			data->minimap->cursor_y -= data->minimap->cursor_y - (y * data->minimap->squareSize + MINIMAP_SIZE / 15);
		else
			data->minimap->cursor_y += STEP;
	}
	else if (input == S)
	{
		if (data->map->map[y - 1][x] == WALL)
			data->minimap->cursor_y -= data->minimap->cursor_y - (y * data->minimap->squareSize + MINIMAP_SIZE / 15);
		else
			data->minimap->cursor_y -= STEP;
	}
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
