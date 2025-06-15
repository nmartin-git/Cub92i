/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:17:16 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/15 21:45:09 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

int get_pixel_color(t_image *image, int x, int y)
{
	char *dst = image->adress + (y * image->l_len + x * (image->bpp / 8));
	return (*(unsigned int *)dst);
}

void	is_xwall(t_data *data, int input)
{
	int	saved;
	int	x;
	int	y;
	int	y2;

	saved = (data->minimap->cursor_x - MINIMAP_SIZE / 15) / data->minimap->pxl_size;
	y = (data->minimap->cursor_y - MINIMAP_SIZE / 15) / data->minimap->pxl_size;
	y2 = (data->minimap->cursor_y - MINIMAP_SIZE / 15 + data->minimap->pxl_size / 1.5) / data->minimap->pxl_size;
	if (input == D)
	{
		x = (data->minimap->cursor_x + data->minimap->pxl_size / 1.5 - MINIMAP_SIZE / 15 + STEP) / data->minimap->pxl_size;
		// if (data->map->map[y2][x] == WALL)
		// 	return ;
		if (data->map->map[y][x] == WALL)
		{
			data->minimap->cursor_x += (x * data->minimap->pxl_size + MINIMAP_SIZE / 15) - (data->minimap->cursor_x + data->minimap->pxl_size / 1.5);
			if (get_pixel_color(data->minimap->minimap, data->minimap->cursor_x + data->minimap->pxl_size / 1.5 - MINIMAP_SIZE / 15, data->minimap->cursor_y - MINIMAP_SIZE / 15) == data->minimap->f_color)
				data->minimap->cursor_x++;
		}
		else
			data->minimap->cursor_x += STEP;
	}
	else if (input == A)
	{
		x = (data->minimap->cursor_x - MINIMAP_SIZE / 15 - STEP) / data->minimap->pxl_size;
		// if (data->map->map[y2][x] == WALL)
		// 	return ;
		if (data->map->map[y][x] == WALL)
			data->minimap->cursor_x -= data->minimap->cursor_x - (saved * data->minimap->pxl_size + MINIMAP_SIZE / 15);
		else
			data->minimap->cursor_x -= STEP;
	}
}

void	is_ywall(t_data *data, int input)
{
	int	saved;
	int	x;
	int	y;

	saved = (data->minimap->cursor_y - MINIMAP_SIZE / 15) / data->minimap->pxl_size;
	x = (data->minimap->cursor_x - MINIMAP_SIZE / 15) / data->minimap->pxl_size;
	if (input == W)
	{
		y = (data->minimap->cursor_y - MINIMAP_SIZE / 15 - STEP) / data->minimap->pxl_size;
		if (data->map->map[y][x] == WALL)
			data->minimap->cursor_y -= data->minimap->cursor_y - (saved * data->minimap->pxl_size + MINIMAP_SIZE / 15);
		else
			data->minimap->cursor_y -= STEP;
	}
	else if (input == S)
	{
		y = (data->minimap->cursor_y + data->minimap->pxl_size / 1.5 - MINIMAP_SIZE / 15 + STEP) / data->minimap->pxl_size;
		if (data->map->map[y][x] == WALL)
		{
			data->minimap->cursor_y += (y * data->minimap->pxl_size + MINIMAP_SIZE / 15) - (data->minimap->cursor_y + data->minimap->pxl_size / 1.5);
			if (get_pixel_color(data->minimap->minimap, data->minimap->cursor_x - MINIMAP_SIZE / 15, data->minimap->cursor_y + data->minimap->pxl_size / 1.5 - MINIMAP_SIZE / 15) == data->minimap->f_color)
				data->minimap->cursor_y++;
		}
		else
			data->minimap->cursor_y += STEP;
	}
}

void	put_cursor_direction(t_minimap *minimap)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	t_pos	point_a;
	
	point_a.x = minimap->direction->tab_x / 2;
	point_a.y = minimap->direction->tab_y / 2;
	x = point_a.x + cos(minimap->p_angle) * minimap->pxl_size;
	y = point_a.y + sin(minimap->p_angle) * minimap->pxl_size;
	dx = x - point_a.x;
	dy = y - point_a.y;
	if (ft_abs(dx) > ft_abs(dy))
		small_angle(minimap->direction, point_a, dx, dy);
	else
		big_angle(minimap->direction, point_a, dx, dy);
}

void	pixel_put_cursor(t_image *cursor, int color, int size, int radius)
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
