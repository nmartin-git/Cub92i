/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:07:59 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/12 18:28:17 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	set_item_rayscast(t_data *data)
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
				item_raycast(data, pos, ((FOV * PI) / 180) / 2,
					data->map->map[pos.y][pos.x]);
			pos.x++;
		}
		pos.y++;
	}
}

int	map_is_wall(t_data *d, t_pos p)
{
	if (d->map->map[p.y / d->mmap->pxl_size][p.x / d->mmap->pxl_size] == WALL
			|| d->map->map[p.y / d->mmap->pxl_size][p.x / d->mmap->pxl_size]
				== C_DOOR)
		return (1);
	return (0);
}

int	small_cast(t_data *data, t_pos pixel, int dx, int dy)
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
		if (map_is_wall(data, pixel))
			return (0);
	}
	return (1);
}

int	big_cast(t_data *data, t_pos pixel, int dx, int dy)
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
		if (map_is_wall(data, pixel))
			return (0);
	}
	return (1);
}

void	item_raycast(t_data *d, t_pos pos, double fov, int item)
{
	t_pos	origin;
	int		tmp;
	float	dot;
	t_float	is_fov;
	t_pos	dst;

	origin.x = d->mmap->cursor_x + d->mmap->pxl_size / 3 - d->mmap->sb15;
	origin.y = d->mmap->cursor_y + d->mmap->pxl_size / 3 - d->mmap->sb15;
	pos.x = (pos.x * d->mmap->pxl_size) + d->mmap->pxl_size / 2;
	pos.y = (pos.y * d->mmap->pxl_size) + d->mmap->pxl_size / 2;
	dst.x = pos.x - origin.x;
	dst.y = pos.y - origin.y;
	tmp = sqrt(dst.x * dst.x + dst.y * dst.y);
	if (tmp == 0)
		return ;
	is_fov.x = dst.x / tmp;
	is_fov.y = dst.y / tmp;
	dot = cos(d->mmap->p_angle) * is_fov.x + sin(d->mmap->p_angle) * is_fov.y;
	if (dot <= cos(fov))
		return ;
	if (ft_abs(dst.x) > ft_abs(dst.y))
		tmp = small_cast(d, origin, dst.x, dst.y);
	else
		tmp = big_cast(d, origin, dst.x, dst.y);
	if (!tmp)
		return ;
	item = 0;
	//item_on_map(d, item, dot, pow(dst.x, 2) + pow(dst.y, 2));
}
