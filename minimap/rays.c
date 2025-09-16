/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/16 16:47:19 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

int	vertical_wall(t_minimap *minimap, t_data *d, t_pos *pos, double angle)
{
	double		n_tan;
	t_double	off;
	t_double	r;
	t_pos		map;
	int			depth_of_field;

	angle = normalize_angle(angle);
	depth_of_field = 0;
	n_tan = -tan(angle);
	if (angle > PI / 2 && angle < 3 * PI / 2)
	{
		r.x = (((int)(minimap->cursor_x + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) / minimap->pxl_size) * minimap->pxl_size) - 1 + MINIMAP_SIZE / 15;
		r.y = (minimap->cursor_x + minimap->pxl_size / 3 - r.x) * n_tan + minimap->cursor_y + minimap->pxl_size / 3;
		off.x = -minimap->pxl_size;
		off.y = -off.x * n_tan;
	}
	else if ((angle >= 0 && angle < PI / 2) || (angle > 3 * PI / 2 && angle < 2 * PI))
	{
		r.x = (((int)(minimap->cursor_x + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) / minimap->pxl_size) * minimap->pxl_size) + minimap->pxl_size + MINIMAP_SIZE / 15;
		r.y = (minimap->cursor_x + minimap->pxl_size / 3 - r.x) * n_tan + minimap->cursor_y + minimap->pxl_size / 3;
		off.x = minimap->pxl_size;
		off.y = -off.x * n_tan;
	}
	else
		return (tan_err(pos), 0);
	while (depth_of_field < d->map->col)
	{
		map.x = (int)(r.x - MINIMAP_SIZE / 15) / minimap->pxl_size;
		map.y = (int)(r.y - MINIMAP_SIZE / 15) / minimap->pxl_size;
		if (map.x >= 0 && map.x < d->map->col && map.y >= 0 && map.y < d->map->row 
			&& (d->map->map[map.y][map.x] == WALL || d->map->map[map.y][map.x] == C_DOOR))
		{
			pos->x = (int)r.x;
			pos->y = (int)r.y;
			if (d->map->map[map.y][map.x] == C_DOOR)
				return (1);
			return (0);
		}
		else if (map.x < 0 || map.x >= d->map->col || map.y < 0 || map.y >= d->map->row)
			return (tan_err(pos), 0);
		else
		{
			r.x += off.x;
			r.y += off.y;
			depth_of_field++;
		}
	}
	tan_err(pos);
	return (0);
}

int	horizontal_wall(t_minimap *minimap, t_data *d, t_pos *pos, double angle)
{
	double		a_tan;
	t_double	off;
	t_double	r;
	t_pos		map;
	int			depth_of_field;

	angle = normalize_angle(angle);
	depth_of_field = 0;
	a_tan = -1 / tan(angle);
	if (angle > PI)
	{
		r.y = (((int)(minimap->cursor_y + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) / minimap->pxl_size) * minimap->pxl_size) - 1 + MINIMAP_SIZE / 15;
		r.x = (minimap->cursor_y + minimap->pxl_size / 3 - r.y) * a_tan + minimap->cursor_x + minimap->pxl_size / 3;
		off.y = -minimap->pxl_size;
		off.x = -off.y * a_tan;
	}
	else if (angle < PI && angle != 0)
	{
		r.y = (((int)(minimap->cursor_y + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) / minimap->pxl_size) * minimap->pxl_size) + minimap->pxl_size + MINIMAP_SIZE / 15;
		r.x = (minimap->cursor_y + minimap->pxl_size / 3 - r.y) * a_tan + minimap->cursor_x + minimap->pxl_size / 3;
		off.y = minimap->pxl_size;
		off.x = -off.y * a_tan;
	}
	else
		return (tan_err(pos), 0);
	while (depth_of_field < d->map->row)
	{
		map.x = (int)(r.x - MINIMAP_SIZE / 15) / minimap->pxl_size;
		map.y = (int)(r.y - MINIMAP_SIZE / 15) / minimap->pxl_size;
		if (map.x >= 0 && map.x < d->map->col && map.y >= 0 && map.y < d->map->row 
			&& (d->map->map[map.y][map.x] == WALL || d->map->map[map.y][map.x] == C_DOOR))
		{
			pos->x = (int)r.x;
			pos->y = (int)r.y;
			if (d->map->map[map.y][map.x] == C_DOOR)
				return (1);
			return (0);
		}
		else if (map.x < 0 || map.x >= d->map->col || map.y < 0 || map.y >= d->map->row)
			return (tan_err(pos), 0);
		else
		{
			r.x += off.x;
			r.y += off.y;
			depth_of_field++;
		}
	}
	return (tan_err(pos), 0);
}

void	ray_percent(t_ray *ray, int result, t_minimap *minimap, long dst)
{
	float	percent;
	float	tmp;

	tmp = ((result - minimap->sb15) / minimap->pxl_size) * minimap->pxl_size;
	percent = (((result - minimap->sb15) - tmp) * QUALITY) / minimap->pxl_size;
	ray->percent = percent;
	ray->dst = dst;
}

void	ray_h_v(t_pos *result, t_pos *p, int h_v, t_ray *ray)
{
	result->x = p->x;
	result->y = p->y;
	ray->x_y = h_v;
}

void	raycast(t_minimap *minimap, t_ray *ray, t_data *data, t_pos *result)
{
	t_pos	ph;
	t_pos	pv;
	t_long	dst;
	t_pos	origin;
	t_pos	door;

	ray->angle = normalize_angle(ray->angle);
	door.x = horizontal_wall(minimap, data, &ph, ray->angle);
	door.y = vertical_wall(minimap, data, &pv, ray->angle);
	origin.x = minimap->cursor_x + minimap->pxl_size / 3;
	origin.y = minimap->cursor_y + minimap->pxl_size / 3;
	if (ph.x == TAN_ERR || ph.y == TAN_ERR)
		dst.x = LONG_MAX;
	else
		dst.x = pow(ph.x - origin.x, 2) + pow(ph.y - origin.y, 2);
	if (pv.x == TAN_ERR || pv.y == TAN_ERR)
		dst.y = LONG_MAX;
	else
		dst.y = pow(pv.x - origin.x, 2) + pow(pv.y - origin.y, 2);
	if (dst.x <= dst.y)
	{
		ray_h_v(result, &ph, HORIZONTAL, ray);
		ray->door = door.x;
		ray_percent(ray, result->x, minimap, dst.x);
	}
	else
	{
		ray_h_v(result, &pv, VERTICAL, ray);
		ray->door = door.y;
		ray_percent(ray, result->y, minimap, dst.y);
	}
}
