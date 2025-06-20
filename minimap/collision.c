/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:52:58 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/20 15:35:13 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	go_left(t_data *data)
{
	int		x;
	int		y;
	int		y2;
	int		wall_edge;
	float	diff;

	x = (data->minimap->cursor_x - MINIMAP_SIZE / 15 - STEP) / data->minimap->pxl_size;
	y = (data->minimap->cursor_y - MINIMAP_SIZE / 15) / data->minimap->pxl_size;
	y2 = (data->minimap->cursor_y - MINIMAP_SIZE / 15 + data->minimap->pxl_size / 1.5 -1) / data->minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y2][x] == WALL)
	{
		wall_edge = (x + 1) * data->minimap->pxl_size + MINIMAP_SIZE / 15;
		diff = data->minimap->cursor_x - wall_edge;
		data->minimap->cursor_x -= diff;
	}
	else
		data->minimap->cursor_x -= STEP;
}

void	go_right(t_data *data)
{
	int	saved;
	int	x;
	int	y;
	int	y2;

	saved = (data->minimap->cursor_x - MINIMAP_SIZE / 15) / data->minimap->pxl_size;
	y = (data->minimap->cursor_y - MINIMAP_SIZE / 15) / data->minimap->pxl_size;
	y2 = (data->minimap->cursor_y - MINIMAP_SIZE / 15 + data->minimap->pxl_size / 1.5 - 1) / data->minimap->pxl_size;
	x = (data->minimap->cursor_x + data->minimap->pxl_size / 1.5 - MINIMAP_SIZE / 15 + STEP) / data->minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y2][x] == WALL)
	{
		data->minimap->cursor_x += (x * data->minimap->pxl_size + MINIMAP_SIZE / 15) - (data->minimap->cursor_x + data->minimap->pxl_size / 1.5);
		if ((x * data->minimap->pxl_size + MINIMAP_SIZE / 15) - (data->minimap->cursor_x + data->minimap->pxl_size / 1.5) < 1 && (x * data->minimap->pxl_size + MINIMAP_SIZE / 15) - (data->minimap->cursor_x + data->minimap->pxl_size / 1.5) > 0)
			data->minimap->cursor_x++;
	}
	else
		data->minimap->cursor_x += STEP;
}

void	go_up(t_data *data)
{
	int		x;
	int		x2;
	int		y;
	int 	wall_edge;
	float	diff;

	x = (data->minimap->cursor_x - MINIMAP_SIZE / 15) / data->minimap->pxl_size;
	x2 = (data->minimap->cursor_x - MINIMAP_SIZE / 15 + data->minimap->pxl_size / 1.5 - 1) / data->minimap->pxl_size;
	y = (data->minimap->cursor_y - MINIMAP_SIZE / 15 - STEP) / data->minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y][x2] == WALL)
	{
		wall_edge = (y + 1) * data->minimap->pxl_size + MINIMAP_SIZE / 15;
		diff = data->minimap->cursor_y - wall_edge;
		data->minimap->cursor_y -= diff;
	}
	else
		data->minimap->cursor_y -= STEP;
}

void	go_down(t_data *data)
{
	int	saved;
	int	x;
	int	x2;
	int	y;

	saved = (data->minimap->cursor_y - MINIMAP_SIZE / 15) / data->minimap->pxl_size;
	x = (data->minimap->cursor_x - MINIMAP_SIZE / 15) / data->minimap->pxl_size;
	x2 = (data->minimap->cursor_x - MINIMAP_SIZE / 15 + data->minimap->pxl_size / 1.5 - 1) / data->minimap->pxl_size;
	y = (data->minimap->cursor_y + data->minimap->pxl_size / 1.5 - MINIMAP_SIZE / 15 + STEP) / data->minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y][x2] == WALL)
	{
		data->minimap->cursor_y += (y * data->minimap->pxl_size + MINIMAP_SIZE / 15) - (data->minimap->cursor_y + data->minimap->pxl_size / 1.5);
		if ((y * data->minimap->pxl_size + MINIMAP_SIZE / 15) - (data->minimap->cursor_y + data->minimap->pxl_size / 1.5) < 1 && (y * data->minimap->pxl_size + MINIMAP_SIZE / 15) - (data->minimap->cursor_y + data->minimap->pxl_size / 1.5) > 0)
			data->minimap->cursor_y++;
	}
	else
		data->minimap->cursor_y += STEP;
}
