/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:52:58 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/04 19:23:49 by igrousso         ###   ########.fr       */
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
	x = (data->screen_minimap->cursor_x - data->screen_minimap->minimap_size_by_15 - pixels) / data->screen_minimap->pxl_size;
	y = (data->screen_minimap->cursor_y - data->screen_minimap->minimap_size_by_15) / data->screen_minimap->pxl_size;
	y2 = (data->screen_minimap->cursor_y - data->screen_minimap->minimap_size_by_15 + data->screen_minimap->pxl_size / 1.5 -1) / data->screen_minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y2][x] == WALL)
	{
		wall_edge = (x + 1) * data->screen_minimap->pxl_size + data->screen_minimap->minimap_size_by_15;
		diff = data->screen_minimap->cursor_x - wall_edge;
		data->screen_minimap->cursor_x -= diff;
	}
	else
		data->screen_minimap->cursor_x -= pixels;	
}

void	go_left(t_data *data, int pixels)
{
	int		x;
	int		y;
	int		y2;
	int		wall_edge;
	float	diff;

	x = (data->minimap->cursor_x - data->minimap->minimap_size_by_15 - pixels) / data->minimap->pxl_size;
	y = (data->minimap->cursor_y - data->minimap->minimap_size_by_15) / data->minimap->pxl_size;
	y2 = (data->minimap->cursor_y - data->minimap->minimap_size_by_15 + data->minimap->pxl_size / 1.5 -1) / data->minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y2][x] == WALL)
	{
		wall_edge = (x + 1) * data->minimap->pxl_size + data->minimap->minimap_size_by_15;
		diff = data->minimap->cursor_x - wall_edge;
		data->minimap->cursor_x -= diff;
	}
	else
		data->minimap->cursor_x -= pixels;
	// data->screen_minimap->cursor_x = data->minimap->cursor_x - data->screen_minimap->pxl_size / 3 + 1;
	go_left_screen(data, pixels / data->minimap->scale);
}

void	go_right_screen(t_data *data, float pixels)
{
	int	x;
	int	y;
	int	y2;

	y = (data->screen_minimap->cursor_y - data->screen_minimap->minimap_size_by_15) / data->screen_minimap->pxl_size;
	y2 = (data->screen_minimap->cursor_y - data->screen_minimap->minimap_size_by_15 + data->screen_minimap->pxl_size / 1.5 - 1) / data->screen_minimap->pxl_size;
	x = (data->screen_minimap->cursor_x + data->screen_minimap->pxl_size / 1.5 - data->screen_minimap->minimap_size_by_15 + pixels) / data->screen_minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y2][x] == WALL)
	{
		data->screen_minimap->cursor_x += (x * data->screen_minimap->pxl_size + data->screen_minimap->minimap_size_by_15) - (data->screen_minimap->cursor_x + data->screen_minimap->pxl_size / 1.5);
		if ((x * data->screen_minimap->pxl_size + data->screen_minimap->minimap_size_by_15) - (data->screen_minimap->cursor_x + data->screen_minimap->pxl_size / 1.5) < 1 && (x * data->screen_minimap->pxl_size + data->screen_minimap->minimap_size_by_15) - (data->screen_minimap->cursor_x + data->screen_minimap->pxl_size / 1.5) > 0)
			data->screen_minimap->cursor_x++;
	}
	else
		data->screen_minimap->cursor_x += pixels;
}

void	go_right(t_data *data, int pixels)
{
	int	x;
	int	y;
	int	y2;

	y = (data->minimap->cursor_y - data->minimap->minimap_size_by_15) / data->minimap->pxl_size;
	y2 = (data->minimap->cursor_y - data->minimap->minimap_size_by_15 + data->minimap->pxl_size / 1.5 - 1) / data->minimap->pxl_size;
	x = (data->minimap->cursor_x + data->minimap->pxl_size / 1.5 - data->minimap->minimap_size_by_15 + pixels) / data->minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y2][x] == WALL)
	{
		data->minimap->cursor_x += (x * data->minimap->pxl_size + data->minimap->minimap_size_by_15) - (data->minimap->cursor_x + data->minimap->pxl_size / 1.5);
		if ((x * data->minimap->pxl_size + data->minimap->minimap_size_by_15) - (data->minimap->cursor_x + data->minimap->pxl_size / 1.5) < 1 && (x * data->minimap->pxl_size + data->minimap->minimap_size_by_15) - (data->minimap->cursor_x + data->minimap->pxl_size / 1.5) > 0)
			data->minimap->cursor_x++;
	}
	else
		data->minimap->cursor_x += pixels;
	// data->screen_minimap->cursor_x = data->minimap->cursor_x - data->screen_minimap->pxl_size / 1.5;
	go_right_screen(data, pixels / data->minimap->scale);
}

void	go_up_screen(t_data *data, float pixels)
{
	int		x;
	int		x2;
	int		y;
	int 	wall_edge;
	float	diff;

	x = (data->screen_minimap->cursor_x - data->screen_minimap->minimap_size_by_15) / data->screen_minimap->pxl_size;
	x2 = (data->screen_minimap->cursor_x - data->screen_minimap->minimap_size_by_15 + data->screen_minimap->pxl_size / 1.5 - 1) / data->screen_minimap->pxl_size;
	y = (data->screen_minimap->cursor_y - data->screen_minimap->minimap_size_by_15 - pixels) / data->screen_minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y][x2] == WALL)
	{
		wall_edge = (y + 1) * data->screen_minimap->pxl_size + data->screen_minimap->minimap_size_by_15;
		diff = data->screen_minimap->cursor_y - wall_edge;
		data->screen_minimap->cursor_y -= diff;
	}
	else
		data->screen_minimap->cursor_y -= pixels;	
}

void	go_up(t_data *data, int pixels)
{
	int		x;
	int		x2;
	int		y;
	int 	wall_edge;
	float	diff;

	x = (data->minimap->cursor_x - data->minimap->minimap_size_by_15) / data->minimap->pxl_size;
	x2 = (data->minimap->cursor_x - data->minimap->minimap_size_by_15 + data->minimap->pxl_size / 1.5 - 1) / data->minimap->pxl_size;
	y = (data->minimap->cursor_y - data->minimap->minimap_size_by_15 - pixels) / data->minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y][x2] == WALL)
	{
		wall_edge = (y + 1) * data->minimap->pxl_size + data->minimap->minimap_size_by_15;
		diff = data->minimap->cursor_y - wall_edge;
		data->minimap->cursor_y -= diff;
	}
	else
		data->minimap->cursor_y -= pixels;
	go_up_screen(data, pixels / data->minimap->scale);
	// data->screen_minimap->cursor_y = data->minimap->cursor_y - data->screen_minimap->pxl_size / 1.5;
}

void	go_down_screen(t_data *data, float pixels)
{
	int	x;
	int	x2;
	int	y;

	x = (data->screen_minimap->cursor_x - data->screen_minimap->minimap_size_by_15) / data->screen_minimap->pxl_size;
	x2 = (data->screen_minimap->cursor_x - data->screen_minimap->minimap_size_by_15 + data->screen_minimap->pxl_size / 1.5 - 1) / data->screen_minimap->pxl_size;
	y = (data->screen_minimap->cursor_y + data->screen_minimap->pxl_size / 1.5 - data->screen_minimap->minimap_size_by_15 + pixels) / data->screen_minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y][x2] == WALL)
	{
		data->screen_minimap->cursor_y += (y * data->screen_minimap->pxl_size + data->screen_minimap->minimap_size_by_15) - (data->screen_minimap->cursor_y + data->screen_minimap->pxl_size / 1.5);
		if ((y * data->screen_minimap->pxl_size + data->screen_minimap->minimap_size_by_15) - (data->screen_minimap->cursor_y + data->screen_minimap->pxl_size / 1.5) < 1 && (y * data->screen_minimap->pxl_size + data->screen_minimap->minimap_size_by_15) - (data->screen_minimap->cursor_y + data->screen_minimap->pxl_size / 1.5) > 0)
			data->screen_minimap->cursor_y++;		
	}
	else
		data->screen_minimap->cursor_y += pixels;	
}

void	go_down(t_data *data, int pixels)
{
	int	x;
	int	x2;
	int	y;

	x = (data->minimap->cursor_x - data->minimap->minimap_size_by_15) / data->minimap->pxl_size;
	x2 = (data->minimap->cursor_x - data->minimap->minimap_size_by_15 + data->minimap->pxl_size / 1.5 - 1) / data->minimap->pxl_size;
	y = (data->minimap->cursor_y + data->minimap->pxl_size / 1.5 - data->minimap->minimap_size_by_15 + pixels) / data->minimap->pxl_size;
	if (data->map->map[y][x] == WALL || data->map->map[y][x2] == WALL)
	{
		data->minimap->cursor_y += (y * data->minimap->pxl_size + data->minimap->minimap_size_by_15) - (data->minimap->cursor_y + data->minimap->pxl_size / 1.5);
		if ((y * data->minimap->pxl_size + data->minimap->minimap_size_by_15) - (data->minimap->cursor_y + data->minimap->pxl_size / 1.5) < 1 && (y * data->minimap->pxl_size + data->minimap->minimap_size_by_15) - (data->minimap->cursor_y + data->minimap->pxl_size / 1.5) > 0)
			data->minimap->cursor_y++;
	}
	else
		data->minimap->cursor_y += pixels;
	go_down_screen(data, pixels / data->minimap->scale);
	// data->screen_minimap->cursor_y = data->minimap->cursor_y - data->screen_minimap->pxl_size / 1.5 - 2;
}
