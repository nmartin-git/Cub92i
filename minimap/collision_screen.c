/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:15:04 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/09 00:47:43 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	go_left_screen(t_data *data, float pixels)
{
	int		x;
	int		y;
	int		y2;
	int		wall_edge;
	float	diff;

	x = (data->sc_mmap->cursor_x - data->sc_mmap->sb15 - pixels) \
		/ data->sc_mmap->pxl_size;
	y = (data->sc_mmap->cursor_y - data->sc_mmap->sb15) \
		/ data->sc_mmap->pxl_size;
	y2 = (data->sc_mmap->cursor_y - data->sc_mmap->sb15 + \
		data->sc_mmap->pxl_size / 1.5 -1) / data->sc_mmap->pxl_size;
	if ((data->map->map[y][x] == WALL || data->map->map[y2][x] == WALL) || \
		(data->map->map[y][x] == C_DOOR || data->map->map[y2][x] == C_DOOR))
	{
		wall_edge = (x + 1) * data->sc_mmap->pxl_size + \
			data->sc_mmap->sb15;
		diff = data->sc_mmap->cursor_x - wall_edge;
		data->sc_mmap->cursor_x -= diff;
	}
	else
		data->sc_mmap->cursor_x -= pixels;
}

void	go_right_screen(t_data *data, float pixels)
{
	int	x;
	int	y;
	int	y2;

	y = (data->sc_mmap->cursor_y - data->sc_mmap->sb15) \
		/ data->sc_mmap->pxl_size;
	y2 = (data->sc_mmap->cursor_y - data->sc_mmap->sb15 \
		+ data->sc_mmap->pxl_size / 1.5 - 1) / data->sc_mmap->pxl_size;
	x = (data->sc_mmap->cursor_x + data->sc_mmap->pxl_size / 1.5 \
		- data->sc_mmap->sb15 + pixels) / data->sc_mmap->pxl_size;
	if ((data->map->map[y][x] == WALL || data->map->map[y2][x] == WALL) || \
		(data->map->map[y][x] == C_DOOR || data->map->map[y2][x] == C_DOOR))
	{
		data->sc_mmap->cursor_x += (x * data->sc_mmap->pxl_size + \
			data->sc_mmap->sb15) - (data->sc_mmap->cursor_x \
			+ data->sc_mmap->pxl_size / 1.5);
		if ((x * data->sc_mmap->pxl_size + data->sc_mmap->sb15) \
		- (data->sc_mmap->cursor_x + data->sc_mmap->pxl_size / 1.5) \
		< 1 && (x * data->sc_mmap->pxl_size + data->sc_mmap->sb15) - \
		(data->sc_mmap->cursor_x + data->sc_mmap->pxl_size / 1.5) > 0)
		data->sc_mmap->cursor_x++;
	}
	else
		data->sc_mmap->cursor_x += pixels;
}

void	go_up_screen(t_data *data, float pixels)
{
	int		x;
	int		x2;
	int		y;
	int		wall_edge;
	float	diff;

	x = (data->sc_mmap->cursor_x - data->sc_mmap->sb15) \
		/ data->sc_mmap->pxl_size;
	x2 = (data->sc_mmap->cursor_x - data->sc_mmap->sb15 \
		+ data->sc_mmap->pxl_size / 1.5 - 1) / data->sc_mmap->pxl_size;
	y = (data->sc_mmap->cursor_y - data->sc_mmap->sb15 - pixels) \
		/ data->sc_mmap->pxl_size;
	if ((data->map->map[y][x] == WALL || data->map->map[y][x2] == WALL) || \
		(data->map->map[y][x] == C_DOOR || data->map->map[y][x2] == C_DOOR))
	{
		wall_edge = (y + 1) * data->sc_mmap->pxl_size + \
			data->sc_mmap->sb15;
		diff = data->sc_mmap->cursor_y - wall_edge;
		data->sc_mmap->cursor_y -= diff;
	}
	else
		data->sc_mmap->cursor_y -= pixels;
}

void	go_down_screen(t_data *data, float pixels)
{
	int	x;
	int	x2;
	int	y;

	x = (data->sc_mmap->cursor_x - data->sc_mmap->sb15) \
		/ data->sc_mmap->pxl_size;
	x2 = (data->sc_mmap->cursor_x - data->sc_mmap->sb15 + \
		data->sc_mmap->pxl_size / 1.5 - 1) / data->sc_mmap->pxl_size;
	y = (data->sc_mmap->cursor_y + data->sc_mmap->pxl_size / 1.5 - \
		data->sc_mmap->sb15 + pixels) / data->sc_mmap->pxl_size;
	if ((data->map->map[y][x] == WALL || data->map->map[y][x2] == WALL) || \
		(data->map->map[y][x] == C_DOOR || data->map->map[y][x2] == C_DOOR))
	{
		data->sc_mmap->cursor_y += (y * data->sc_mmap->pxl_size + \
			data->sc_mmap->sb15) - (data->sc_mmap->cursor_y \
				+ data->sc_mmap->pxl_size / 1.5);
		if ((y * data->sc_mmap->pxl_size + data->sc_mmap->sb15) \
		- (data->sc_mmap->cursor_y + data->sc_mmap->pxl_size / 1.5) \
		< 1 && (y * data->sc_mmap->pxl_size + data->sc_mmap->sb15) - \
		(data->sc_mmap->cursor_y + data->sc_mmap->pxl_size / 1.5) > 0)
		data->sc_mmap->cursor_y++;
	}
	else
		data->sc_mmap->cursor_y += pixels;
}
