/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/18 14:49:52 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

int	is_wall(t_minimap *minimap, t_data *data, t_pos *pos)
{
	int	x_wall;
	int	y_wall;
	
	if (pos->x == TAN_ERR || pos->y == TAN_ERR)
		return (1);
	x_wall = (pos->x - MINIMAP_SIZE / 15 - minimap->pxl_size / 3) / minimap->pxl_size;
	y_wall = (pos->y - MINIMAP_SIZE / 15 /*- minimap->pxl_size / 3*/) / minimap->pxl_size;
	if (x_wall >= data->map->col || y_wall >= data->map->row
		|| x_wall < 0 || y_wall < 0)
		return (1);
	if (data->map->map[y_wall][x_wall] == WALL)
		return (1);
	else
		return (0);
}

void	vertical_wall(t_minimap *minimap, t_data *data, t_pos *pos, double angle)
{
	int	x;
	int	y;

	if (cos(angle) > 0)
		x = minimap->pxl_size;
	else
		x = minimap->pxl_size * -1;
	y = x * tan(angle);
	while (!is_wall(minimap, data, pos))
	{
		pos->x += x;
		pos->y += y;
	}
}

void	horizontal_wall(t_minimap *minimap, t_data *data, t_pos *pos, double angle)
{
	int	x;
	int	y;

	if (sin(angle) > 0)
		y = minimap->pxl_size;
	else
		y = minimap->pxl_size * -1;
	if (fabs(tan(angle)) < 0.001)
	{
		pos->x = TAN_ERR;
		pos->y = TAN_ERR;
	}
	else
		x = y / tan(angle);
	while (!is_wall(minimap, data, pos))
	{
		pos->x += x;
		pos->y += y;
	}
}

void	set_nearest(t_minimap *minimap, t_pos *ph, t_pos *pv, double angle)
{
	ph->y = (int)floor((minimap->cursor_y + minimap->pxl_size / 3) / minimap->pxl_size);
	if (sin(angle) < 0)
		ph->y = ph->y * minimap->pxl_size - 1 + minimap->pxl_size / 3;
	else
		ph->y = ph->y * minimap->pxl_size + minimap->pxl_size + minimap->pxl_size / 3;
	if (fabs(tan(angle)) < 0.001)
	{
		ph->x = TAN_ERR;
		ph->y = TAN_ERR;
	}
	else
		ph->x = (ph->y - (minimap->cursor_y + minimap->pxl_size / 3)) / tan(angle) + (minimap->cursor_x + minimap->pxl_size / 3);
	pv->x = (int)floor((minimap->cursor_x /*+ minimap->pxl_size / 3*/) / minimap->pxl_size);
	if (cos(angle) > 0)
		pv->x = pv->x * minimap->pxl_size + minimap->pxl_size + minimap->pxl_size / 3;
	else
		pv->x = pv->x * minimap->pxl_size - 1 + minimap->pxl_size / 3;
	if (fabs(cos(angle)) < 0.0001)
	{
		pv->x = TAN_ERR;
		pv->y = TAN_ERR;
	}
	else
		pv->y = (minimap->cursor_y) + (pv->x -minimap->cursor_x) * tan(angle);
}

t_pos	*raycast(t_minimap *minimap, double angle, t_data *data, t_pos *result)
{
	t_pos	ph;
	t_pos	pv;
	int		dst1;
	int		dst2;

	set_nearest(minimap, &ph, &pv, angle);
	horizontal_wall(minimap, data, &ph, angle);
	vertical_wall(minimap, data, &pv, angle);
	dst1 = sqrt(pow(ph.x - minimap->cursor_x + minimap->pxl_size / 3, 2) + pow(minimap->cursor_y + minimap->pxl_size / 3 - ph.y, 2));
	dst2 = sqrt(pow(pv.x - minimap->cursor_x + minimap->pxl_size / 3, 2) + pow(minimap->cursor_y + minimap->pxl_size / 3 - pv.y, 2));
	// printf("%d (%d, %d) < %d (%d, %d)\n", dst1, ph.x, ph.y, dst2, pv.x, pv.y);
	if (dst1 < dst2)
		*result = ph;
	else
		*result = pv;
	// *result = ph;
	result->x -= MINIMAP_SIZE / 15;
	result->y -= MINIMAP_SIZE / 15;
	return (result);
}
