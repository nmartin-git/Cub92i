/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/08 14:32:37 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

int	is_wall(t_minimap *minimap, t_data *data, t_pos *pos)
{
	int	x_wall;
	int	y_wall;

	if (pos->x == TAN_ERR || pos->y == TAN_ERR)
		return (1);
	x_wall = (pos->x - MINIMAP_SIZE / 15) / minimap->pxl_size;
	y_wall = (pos->y - MINIMAP_SIZE / 15) / minimap->pxl_size;
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
		x = -minimap->pxl_size;
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
		y = -minimap->pxl_size;
	if (fabs(tan(angle)) < 0.001)
	{
		pos->x = TAN_ERR;
		pos->y = TAN_ERR;
	}
	else
		x = y / tan(angle);
	// if (!is_wall(minimap, data, pos))
	// {
	// 	pos->x += 1;
	// 	pos->y += 1;
	// 	if (is_wall(minimap, data, pos))
	// 		return ;
	// 	pos->x -= 1;
	// 	pos->y -= 1;
	// }//fix corner bug
	while (!is_wall(minimap, data, pos))
	{
		pos->x += x;
		pos->y += y;
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
	if (sin(angle) > 0)
		ph->y = (grid_y + 1) * minimap->pxl_size + MINIMAP_SIZE / 15;
	else if (sin(angle) < 0)
		ph->y = grid_y * minimap->pxl_size + MINIMAP_SIZE / 15 - 1;
	else
	{
		ph->x = TAN_ERR;
		ph->y = TAN_ERR;
	}
	if (ph->x != TAN_ERR && fabs(tan(angle)) > 0.001)
		ph->x = player_x + (ph->y - player_y) / tan(angle);
	else if (fabs(tan(angle)) <= 0.001)
	{
		ph->x = TAN_ERR;
		ph->y = TAN_ERR;
	}
	grid_x = (int)floor((player_x - MINIMAP_SIZE / 15) / minimap->pxl_size);
	if (cos(angle) > 0)
		pv->x = (grid_x + 1) * minimap->pxl_size + MINIMAP_SIZE / 15;
	else if (cos(angle) < 0)
		pv->x = grid_x * minimap->pxl_size + MINIMAP_SIZE / 15 - 1;
	else
	{
		pv->x = TAN_ERR;
		pv->y = TAN_ERR;
	}
	if (pv->x != TAN_ERR && fabs(cos(angle)) > 0.0001)
		pv->y = player_y + (pv->x - player_x) * tan(angle);
	else if (fabs(cos(angle)) <= 0.0001)
	{
		pv->x = TAN_ERR;
		pv->y = TAN_ERR;
	}
}

t_pos	*raycast(t_minimap *minimap, double angle, t_data *data, t_pos *result)
{
	t_pos	ph;
	t_pos	pv;
	long	dst1;
	long	dst2;
	int		x_origin;
	int		y_origin;

	set_nearest(minimap, &ph, &pv, angle);
	(void)data;
	horizontal_wall(minimap, data, &ph, angle);
	vertical_wall(minimap, data, &pv, angle);
	x_origin = minimap->cursor_x + minimap->pxl_size / 3;
	y_origin = minimap->cursor_y + minimap->pxl_size / 3;
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
	}
	else
	{
		result->x = pv.x;
		result->y = pv.y;
	}
	result->x -= MINIMAP_SIZE / 15;
	result->y -= MINIMAP_SIZE / 15;
	// if (result->x + MINIMAP_SIZE / 15 == TAN_ERR || result->y + MINIMAP_SIZE / 15 == TAN_ERR)
	// 	return (NULL);
	return (result);
}
