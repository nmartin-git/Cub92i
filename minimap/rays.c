/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/17 18:20:22 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

int	vertical_wall(t_minimap *m, t_data *d, t_pos *pos, double a)
{
	double		n_tan;
	t_double	off;
	t_double	r;
	t_pos		p;
	int			depth_of_field;

	gagner_5lignes(a, &r, m, &n_tan);
	if (a > PI / 2 && a < 3 * PI / 2)
		off_norm(&off, -m->pxl_size, m->pxl_size * n_tan, &depth_of_field);
	else if ((a >= 0 && a < PI / 2) || (a > 3 * PI / 2 && a < 2 * PI))
		off_norm(&off, m->pxl_size, -m->pxl_size * n_tan, &depth_of_field);
	else
		return (tan_err(pos), 0);
	while (depth_of_field < d->map->col)
	{
		juste_pour_1ligne(&p, &r, m->pxl_size);
		if (p.x >= 0 && p.x < d->map->col && p.y >= 0 && p.y < d->map->row
			&& (d->map->map[p.y][p.x] == 1 || d->map->map[p.y][p.x] == C_DOOR))
			return (wall_norm_de_neuille(&r, pos, d->map->map[p.y][p.x]));
		else if (p.x < 0 || p.x >= d->map->col || p.y < 0 || p.y >= d->map->row)
			return (tan_err(pos), 0);
		else
			wall_norm(&r, &off, &depth_of_field);
	}
	return (tan_err(pos), 0);
}

int	horizontal_wall(t_minimap *m, t_data *d, t_pos *pos, double a)
{
	double		a_tan;
	t_double	off;
	t_double	r;
	t_pos		p;
	int			depth_of_field;

	gagner_4lignes(a, &r, m, &a_tan);
	if (a > PI)
		off_norm(&off, m->pxl_size * a_tan, -m->pxl_size, &depth_of_field);
	else if (a < PI && a != 0)
		off_norm(&off, -m->pxl_size * a_tan, m->pxl_size, &depth_of_field);
	else
		return (tan_err(pos), 0);
	while (depth_of_field < d->map->row)
	{
		juste_pour_1ligne(&p, &r, m->pxl_size);
		if (p.x >= 0 && p.x < d->map->col && p.y >= 0 && p.y < d->map->row
			&& (d->map->map[p.y][p.x] == 1 || d->map->map[p.y][p.x] == C_DOOR))
			return (wall_norm_de_neuille(&r, pos, d->map->map[p.y][p.x]));
		else if (p.x < 0 || p.x >= d->map->col || p.y < 0 || p.y >= d->map->row)
			return (tan_err(pos), 0);
		else
			wall_norm(&r, &off, &depth_of_field);
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
	door.x = horizontal_wall(minimap, data, &ph, normalize_angle(ray->angle));
	door.y = vertical_wall(minimap, data, &pv, normalize_angle(ray->angle));
	origin.x = minimap->cursor_x + minimap->pxl_size / 3;
	origin.y = minimap->cursor_y + minimap->pxl_size / 3;
	raycast_norm(&ph, &pv, &origin, &dst);
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
