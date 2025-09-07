/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:52:58 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/07 21:26:24 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	go_left(t_data *data, int pixels)
{
	int		x;
	int		y;
	int		y2;
	int		wall_edge;
	float	diff;

	x = (data->mmap->cursor_x - data->mmap->SB15 - pixels) / \
		data->mmap->pxl_size;
	y = (data->mmap->cursor_y - data->mmap->SB15) / data->mmap->pxl_size;
	y2 = (data->mmap->cursor_y - data->mmap->SB15 + data->mmap->pxl_size / \
		1.5 -1) / data->mmap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y2][x] == WALL)
	{
		wall_edge = (x + 1) * data->mmap->pxl_size + data->mmap->SB15;
		diff = data->mmap->cursor_x - wall_edge;
		data->mmap->cursor_x -= diff;
	}
	else
		data->mmap->cursor_x -= pixels;
	go_left_screen(data, pixels / data->mmap->scale);
}

void	go_right(t_data *data, int pixels)
{
	int	x;
	int	y;
	int	y2;

	y = (data->mmap->cursor_y - data->mmap->SB15) / data->mmap->pxl_size;
	y2 = (data->mmap->cursor_y - data->mmap->SB15 + data->mmap->pxl_size / \
		1.5 - 1) / data->mmap->pxl_size;
	x = (data->mmap->cursor_x + data->mmap->pxl_size / 1.5 - \
			data->mmap->SB15 + pixels) / data->mmap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y2][x] == WALL)
	{
		data->mmap->cursor_x += (x * data->mmap->pxl_size + \
			data->mmap->SB15) - (data->mmap->cursor_x + \
			data->mmap->pxl_size / 1.5);
		if ((x * data->mmap->pxl_size + data->mmap->SB15) - \
			(data->mmap->cursor_x + data->mmap->pxl_size / 1.5) < 1 \
			&& (x * data->mmap->pxl_size + data->mmap->SB15) - \
			(data->mmap->cursor_x + data->mmap->pxl_size / 1.5) > 0)
			data->mmap->cursor_x++;
	}
	else
		data->mmap->cursor_x += pixels;
	go_right_screen(data, pixels / data->mmap->scale);
}

void	go_up(t_data *data, int pixels)
{
	int		x;
	int		x2;
	int		y;
	int		wall_edge;
	float	diff;

	x = (data->mmap->cursor_x - data->mmap->SB15) / data->mmap->pxl_size;
	x2 = (data->mmap->cursor_x - data->mmap->SB15 + data->mmap->pxl_size / \
		1.5 - 1) / data->mmap->pxl_size;
	y = (data->mmap->cursor_y - data->mmap->SB15 - pixels) / \
		data->mmap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y][x2] == WALL)
	{
		wall_edge = (y + 1) * data->mmap->pxl_size + data->mmap->SB15;
		diff = data->mmap->cursor_y - wall_edge;
		data->mmap->cursor_y -= diff;
	}
	else
		data->mmap->cursor_y -= pixels;
	go_up_screen(data, pixels / data->mmap->scale);
}

void	go_down(t_data *data, int pixels)
{
	int	x;
	int	x2;
	int	y;

	x = (data->mmap->cursor_x - data->mmap->SB15) / data->mmap->pxl_size;
	x2 = (data->mmap->cursor_x - data->mmap->SB15 + data->mmap->pxl_size / \
		1.5 - 1) / data->mmap->pxl_size;
	y = (data->mmap->cursor_y + data->mmap->pxl_size / 1.5 - data->mmap->SB15 \
		+ pixels) / data->mmap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y][x2] == WALL)
	{
		data->mmap->cursor_y += (y * data->mmap->pxl_size + data->mmap->SB15) \
			- (data->mmap->cursor_y + data->mmap->pxl_size / 1.5);
		if ((y * data->mmap->pxl_size + data->mmap->SB15) - \
			(data->mmap->cursor_y + data->mmap->pxl_size / 1.5) < 1 && (y * \
			data->mmap->pxl_size + data->mmap->SB15) - (data->mmap->cursor_y \
			+ data->mmap->pxl_size / 1.5) > 0)
			data->mmap->cursor_y++;
	}
	else
		data->mmap->cursor_y += pixels;
	go_down_screen(data, pixels / data->mmap->scale);
}
