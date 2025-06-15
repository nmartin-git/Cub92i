/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/16 01:20:49 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

int	is_wall(t_minimap *minimap, int **map, t_pos *pos)
{
	int	x_wall;
	int	y_wall;

	x_wall = (pos->x - MINIMAP_SIZE / 15) / minimap->pxl_size;
	y_wall = (pos->y - MINIMAP_SIZE / 15) / minimap->pxl_size;
	if (x_wall < 0 || y_wall < 0
		|| x_wall >= 29
		|| y_wall >= 12)
		return (1);
	if (map[y_wall][x_wall] == WALL)
		return (1);
	else
		return (0);
}

void	vertical_wall(t_minimap *minimap, int **map, t_pos *pos, double angle)
{
	int	x;
	int	y;

	if (cos(angle) > 0)
		x = minimap->pxl_size;
	else
		x = minimap->pxl_size * -1;
	y = x * tan(angle);
	while (!is_wall(minimap, map, pos))
	{
		pos->x += x;
		pos->y += y;
	}
}

void	horizontal_wall(t_minimap *minimap, int **map, t_pos *pos, double angle)
{
	int	x;
	int	y;

	if (sin(angle) < 0)
		y = minimap->pxl_size;
	else
		y = minimap->pxl_size * -1;
	if (tan(angle) > -0.0001 && tan(angle) < 0.001)
		x = 0;
	else
		x = y / tan(angle);
	while (!is_wall(minimap, map, pos))
	{
		pos->x += x;
		pos->y += y;
	}
}

void	set_nearest(t_minimap *minimap, t_pos *ph, t_pos *pv, double angle)
{
	ph->y = (int)floor((minimap->cursor_y - MINIMAP_SIZE / 15 + minimap->pxl_size / 3) / minimap->pxl_size);
	if (sin(angle) < 0)
		ph->y = ph->y * minimap->pxl_size - 1;
	else
		ph->y = ph->y * minimap->pxl_size + minimap->pxl_size;
	if (tan(angle) > -0.0001 && tan(angle) < 0.001)
		ph->x = minimap->cursor_x + MINIMAP_SIZE;
	else
		ph->x = (ph->y - (minimap->cursor_y - MINIMAP_SIZE / 15 + minimap->pxl_size / 3)) / tan(angle) + (minimap->cursor_x - MINIMAP_SIZE / 15);
	pv->x = (int)floor((minimap->cursor_x - MINIMAP_SIZE / 15) / minimap->pxl_size);
	if (cos(angle) > 0)
		pv->x = pv->x * minimap->pxl_size + minimap->pxl_size;
	else
		pv->x = pv->x * minimap->pxl_size - 1;
	// printf("%d + (%d - %d) * %f (tan(%f))\n", minimap->cursor_y, minimap->cursor_x, pv->x, tan(angle), angle);
	if (fabs(cos(angle)) < 0.0001)
		pv->y = minimap->cursor_y + MINIMAP_SIZE;
	else
		pv->y = (minimap->cursor_y - MINIMAP_SIZE / 15) + (minimap->cursor_x - pv->x) * tan(angle);
}

t_pos	*raycast(t_minimap *minimap, double angle, int **map, t_pos *result)
{
	t_pos	ph;
	t_pos	pv;
	int		dst1;
	int		dst2;

	set_nearest(minimap, &ph, &pv, angle);
	(void)map;
	// horizontal_wall(minimap, map, &ph, angle);
	// vertical_wall(minimap, map, &pv, angle);
	dst1 = sqrt(pow(ph.x - minimap->cursor_x - MINIMAP_SIZE / 15 + minimap->pxl_size / 3, 2) + pow(minimap->cursor_y - MINIMAP_SIZE / 15 + minimap->pxl_size / 3 - ph.y, 2));
	dst2 = sqrt(pow(pv.x - minimap->cursor_x - MINIMAP_SIZE / 15 + minimap->pxl_size / 3, 2) + pow(minimap->cursor_y - MINIMAP_SIZE / 15 + minimap->pxl_size / 3 - pv.y, 2));
	printf("%d (%d, %d) < %d (%d, %d)\n", dst1, ph.x, ph.y, dst2, pv.x, pv.y);
	// if (dst1 < dst2)
	// 	*result = ph;
	// else
	// 	*result = pv;
	*result = pv;
	return (result);
}
