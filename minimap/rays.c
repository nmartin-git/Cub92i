/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/19 19:38:24 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	tan_err(t_pos *pos)
{
	pos->x = TAN_ERR;
	pos->y = TAN_ERR;
}

int	is_wall(t_minimap *minimap, t_data *data, t_pos *pos, t_pos *diff)
{
	int	x_wall;
	int	y_wall;

	if (pos->x == TAN_ERR || pos->y == TAN_ERR)
		return (1);
	if (diff)
	{
		x_wall = (pos->x + diff->x - MINIMAP_SIZE / 15) / minimap->pxl_size;
		y_wall = (pos->y + diff->y - MINIMAP_SIZE / 15) / minimap->pxl_size;
	}
	else
	{
		x_wall = (pos->x - MINIMAP_SIZE / 15) / minimap->pxl_size;
		y_wall = (pos->y - MINIMAP_SIZE / 15) / minimap->pxl_size;
	}
	if (x_wall >= data->map->col || y_wall >= data->map->row
		|| x_wall < 0 || y_wall < 0)
		return (1);
	if (data->map->map[y_wall][x_wall] == WALL)
		return (1);
	else
		return (0);
}

int	is_inside_wall(t_minimap *minimap, t_pos *pos)
{
	int	x;
	int	y;

	x = pos->x/* - MINIMAP_SIZE / 15*/;
	y = pos->y/* - MINIMAP_SIZE / 15*/;
	// printf("%d, %d\n", x, y);
	if (x > minimap->minimap->tab_x || y > minimap->minimap->tab_y)
		return (1);
	if (get_pixel_img(minimap->minimap, x, y) == minimap->w_color)
		return (1);
	else
		return (0);
}

void	vertical_wall(t_minimap *minimap, t_data *d, t_pos *pos, double angle)
{
	t_pos	step;
	t_pos	diff;
	// t_pos	diff2;
	int		neg;

	if (cos(angle) >= 0)
		neg = 1;
	else
		neg = -1;
	// if (sin(angle) < 0)
	// 	neg2 = 1;
	// else
	// 	neg2 = -1;
	diff.x = neg;
	diff.y = 0;
	step.x = minimap->pxl_size * neg;
	step.y = step.x * tan(angle);
	while (!is_wall(minimap, d, pos, &diff))
	{
		pos->x += step.x;
		pos->y += step.y;
	}
}

void	horizontal_wall(t_minimap *minimap, t_data *d, t_pos *pos, double angle)
{
	t_pos	step;
	t_pos	diff;
	// t_pos	diff2;
	int		neg;

	if (sin(angle) >= 0)
		neg = 1;
	else
		neg = -1;
	// if (cos(angle) > 0)
	// 	neg2 = 1;
	// else
	// 	neg2 = -1;
	diff.x = 0;
	diff.y = neg;
	step.y = minimap->pxl_size * neg;
	if (fabs(tan(angle)) < 0.001)
		tan_err(pos);
	else
		step.x = step.y / tan(angle);
	while (!is_wall(minimap, d, pos, &diff))
	{
		pos->x += step.x;
		pos->y += step.y;
	}
}

void	set_nearest(t_minimap *minimap, t_pos *ph, t_pos *pv, double angle)
{
	int	player_x;
	int	player_y;
	int	grid_x;
	int	grid_y;

	player_x = minimap->cursor_x + minimap->pxl_size / 3;
	player_y = minimap->cursor_y + minimap->pxl_size / 3;
	grid_y = (int)floor((player_y - MINIMAP_SIZE / 15) / minimap->pxl_size);
	ph->x = 0;
	pv->y = 0;
	if (sin(angle) > 0)
		ph->y = (grid_y + 1) * minimap->pxl_size + MINIMAP_SIZE / 15 - 1;
	else if (sin(angle) < 0)
		ph->y = grid_y * minimap->pxl_size + MINIMAP_SIZE / 15/* - 1*/;
	else
		tan_err(ph);
	if (ph->x != TAN_ERR && fabs(tan(angle)) > 0.001)
		ph->x = player_x + (ph->y - player_y) / tan(angle);
	else if (fabs(tan(angle)) <= 0.001)
		tan_err(ph);
	grid_x = (int)floor((player_x - MINIMAP_SIZE / 15) / minimap->pxl_size);
	if (cos(angle) > 0)
		pv->x = (grid_x + 1) * minimap->pxl_size + MINIMAP_SIZE / 15 - 1;
	else if (cos(angle) < 0)
		pv->x = grid_x * minimap->pxl_size + MINIMAP_SIZE / 15/* - 1*/;
	else
		tan_err(pv);
	if (pv->x != TAN_ERR && fabs(cos(angle)) > 0.0001)
		pv->y = player_y + (pv->x - player_x) * tan(angle);
	else if (fabs(cos(angle)) <= 0.0001)
		tan_err(pv);
}

t_ray	*raycast(t_minimap *minimap, t_ray *ray, t_data *data, t_pos *result)
{
	t_pos	ph;
	t_pos	pv;
	long	dst1;
	long	dst2;
	int		x_origin;
	int		y_origin;

	set_nearest(minimap, &ph, &pv, ray->angle);
	horizontal_wall(minimap, data, &ph, ray->angle);
	vertical_wall(minimap, data, &pv, ray->angle);
	x_origin = minimap->cursor_x + minimap->pxl_size / 3;
	y_origin = minimap->cursor_y + minimap->pxl_size / 3;
	// ph.x = TAN_ERR;
	if (ph.x == TAN_ERR || ph.y == TAN_ERR)
		dst1 = LONG_MAX;
	else
		dst1 = pow(ph.x - x_origin, 2) + pow(ph.y - y_origin, 2);
	if (pv.x == TAN_ERR || pv.y == TAN_ERR)
		dst2 = LONG_MAX;
	else
		dst2 = pow(pv.x - x_origin, 2) + pow(pv.y - y_origin, 2);
	if (dst1 <= dst2)
	{
		result->x = ph.x;
		result->y = ph.y;
		ray->dst = dst1;
		ray->x_y = HORIZONTAL;
		ray->percent = (result->x - MINIMAP_SIZE / 15) / minimap->pxl_size;
		ray->percent = (result->x - MINIMAP_SIZE / 15) - (ray->percent * minimap->pxl_size);
		ray->percent = (ray->percent * QUALITY) / minimap->pxl_size;
	}
	else
	{
		result->x = pv.x;
		result->y = pv.y;
		ray->dst = dst2;
		ray->x_y = VERTICAL;
		ray->percent = (result->y - MINIMAP_SIZE / 15) / minimap->pxl_size;
		ray->percent = (result->y - MINIMAP_SIZE / 15) - (ray->percent * minimap->pxl_size);
		ray->percent = (ray->percent * QUALITY) / minimap->pxl_size;
	}
	result->x -= MINIMAP_SIZE / 15;
	result->y -= MINIMAP_SIZE / 15;
	// if (result->x + MINIMAP_SIZE / 15 == TAN_ERR || result->y + MINIMAP_SIZE / 15 == TAN_ERR)
	// 	return (NULL);
	return (ray);
}
