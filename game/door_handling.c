/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:47:30 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/13 21:48:44 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	open_close_door2(t_data *data)
{
	int	x;
	int	y;

	x = data->sc_mmap->cursor_x - data->sc_mmap->sb15 + cos(data->mmap->p_angle)
		* data->sc_mmap->pxl_size * 1.5;
	y = data->sc_mmap->cursor_y - data->sc_mmap->sb15 + sin(data->mmap->p_angle)
		* data->sc_mmap->pxl_size * 1.5;
	x /= data->sc_mmap->pxl_size;
	y /= data->sc_mmap->pxl_size;
	if (data->map->map[y][x] == C_DOOR)
		data->map->map[y][x] = O_DOOR;
	else if (data->map->map[y][x] == O_DOOR)
		data->map->map[y][x] = C_DOOR;
}

void	open_close_door(t_data *data)
{
	int	x;
	int	y;

	x = (data->sc_mmap->cursor_x - data->sc_mmap->sb15)
		/ data->sc_mmap->pxl_size;
	y = (data->sc_mmap->cursor_y - data->sc_mmap->sb15)
		/ data->sc_mmap->pxl_size;
	if (data->map->map[y][x] == O_DOOR || data->map->map[y][x] == C_DOOR)
		return ;
	x = data->sc_mmap->cursor_x - data->sc_mmap->sb15 + cos(data->mmap->p_angle)
		* 4;
	y = data->sc_mmap->cursor_y - data->sc_mmap->sb15 + sin(data->mmap->p_angle)
		* 4;
	x /= data->sc_mmap->pxl_size;
	y /= data->sc_mmap->pxl_size;
	if (data->map->map[y][x] == C_DOOR)
		data->map->map[y][x] = O_DOOR;
	else if (data->map->map[y][x] == O_DOOR)
		data->map->map[y][x] = C_DOOR;
	if (data->map->map[y][x] == O_DOOR || data->map->map[y][x] == C_DOOR)
		return ;
	open_close_door2(data);
}
