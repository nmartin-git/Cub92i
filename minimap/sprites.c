/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:07:59 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/15 17:01:53 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

int	map_is_wall(t_data *d, t_pos p)
{
	if (d->map->map[p.y / d->mmap->pxl_size][p.x / d->mmap->pxl_size] == WALL
		|| d->map->map[p.y / d->mmap->pxl_size][p.x
		/ d->mmap->pxl_size] == C_DOOR)
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

static void	calculate_angle(t_data *d, int item, t_float is_fov, t_pos dst)
{
	float	rel_angle;

	rel_angle = atan2(is_fov.y, is_fov.x) - d->mmap->p_angle;
	while (rel_angle < -PI)
		rel_angle += 2 * PI;
	while (rel_angle > PI)
		rel_angle -= 2 * PI;
	item_on_map(d, item, (rel_angle + (((FOV * PI) / 180) / 2)) / (2 * \
				(((FOV * PI) / 180) / 2)) * 100, sqrt(dst.x * dst.x + \
					dst.y * dst.y));
}

void	item_raycast(t_data *d, t_pos pos, int item)
{
	t_pos	origin;
	float	tmp;
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
	if (ft_abs(dst.x) > ft_abs(dst.y))
		tmp = small_cast(d, origin, dst.x, dst.y);
	else
		tmp = big_cast(d, origin, dst.x, dst.y);
	if (!tmp)
		return ;
	calculate_angle(d, item, is_fov, dst);
}
