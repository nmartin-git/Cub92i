/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:07:59 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/10 17:52:40 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	set_item_rayscast(t_data *data)//faire conditon que si y a puff ou mordjene sur la minimap
{
	t_pos	pos;

	pos.y = 0;
	while (pos.y < data->mmap->y)
	{
		pos.x = 0;
		while (pos.x < data->mmap->x)
		{
			if (data->map->map[pos.y][pos.x] == MORDJENE
				|| data->map->map[pos.y][pos.x] == PUFF)
				item_raycast(data, pos, ((FOV * PI) / 180) / 2);
			pos.x++;
		}
		pos.y++;
	}
}

void	small_cast(t_data *data, t_pos pixel, int dx, int dy)
{
	int	i;
	int	decision;

	i = 0;
	decision = 2 * ft_abs(dy) - ft_abs(dx);
	while (i++ < ft_abs(dx))
	{
		if (dx > 0)
			pixel.x++;
		else
			pixel.x--;
		if (decision < 0)
			decision += 2 * ft_abs(dy);
		else
		{
			decision += 2 * ft_abs(dy) - 2 * ft_abs(dx);
			if (dy > 0)
				pixel.y++;
			else
				pixel.y--;
		}
		if (data->map->map[pixel.y / data->mmap->pxl_size][pixel.x / data->mmap->pxl_size] == WALL
			|| data->map->map[pixel.y / data->mmap->pxl_size][pixel.x / data->mmap->pxl_size] == C_DOOR)
			return ;
	}
}

void	big_cast(t_data *data, t_pos pixel, int dx, int dy)
{
	int	i;
	int	decision;
	i = 0;
	decision = 2 * ft_abs(dx) - ft_abs(dy);
	while (i++ < ft_abs(dy))
	{
		if (dy > 0)
			pixel.y++;
		else
			pixel.y--;
		if (decision < 0)
			decision += 2 * ft_abs(dx);
		else
		{
			decision += 2 * ft_abs(dx) - 2 * ft_abs(dy);
			if (dx > 0)
				pixel.x++;
			else
				pixel.x--;
		}
		if (data->map->map[pixel.y / data->mmap->pxl_size][pixel.x / data->mmap->pxl_size] == WALL
			|| data->map->map[pixel.y / data->mmap->pxl_size][pixel.x / data->mmap->pxl_size] == C_DOOR)
			return ;
	}
}

void	item_raycast(t_data *data, t_pos pos, double fov)
{
	t_pos	origin;
	int		tmp;
	t_pos	is_in_fov;
	int		dx;
	int		dy;
	
	origin.x = data->mmap->cursor_x + data->mmap->pxl_size / 3 - data->mmap->sb15;
	origin.y = data->mmap->cursor_y + data->mmap->pxl_size / 3 - data->mmap->sb15;
	pos.x = (pos.x * data->mmap->pxl_size) + data->mmap->pxl_size / 2;
	pos.y = (pos.y * data->mmap->pxl_size) + data->mmap->pxl_size / 2;
	dx = pos.x - origin.x;
	dy = pos.y - origin.y;
	tmp = sqrt(dx * dx + dy * dy);
	if (tmp == 0)
		return ;
	is_in_fov.x = dx / tmp;
	is_in_fov.y = dy / tmp;
	tmp = cos(data->mmap->p_angle) * is_in_fov.x + sin(data->mmap->p_angle) * is_in_fov.y;
	if (acos(tmp) > data->mmap->p_angle + fov || acos(tmp) < data->mmap->p_angle - fov)
		printf("pas visible\n");
	else
		printf("visible\n");
	// return ;
	// if (ft_abs(dx) > ft_abs(dy))
	// 	small_cast(data->mmap, origin, dx, dy);
	// else
	// 	big_cast(data->mmap, origin, dx, dy);
}
