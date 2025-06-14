/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/14 19:34:22 by nmartin          ###   ########.fr       */
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

	if (sin(angle) > 0)
		y = minimap->pxl_size;
	else
		y = minimap->pxl_size * -1;
	if (tan(angle) > -0.0001 && tan(angle) < 0.001)
		x = y / 0.0001;
	else
		x = y / tan(angle);
	while (!is_wall(minimap, map, pos))
	{
		pos->x += x;
		pos->y += y;
	}
}

void	set_nearest(t_minimap *minimap, t_pos *p1, t_pos *p2, double angle)
{
	p1->y = (minimap->cursor_y - MINIMAP_SIZE / 15) / minimap->pxl_size;
	if (sin(angle) < 0)
		p1->y = p1->y * minimap->pxl_size - 1;
	else
		p1->y *= minimap->pxl_size + 1;
	p1->x = (p1->y - minimap->cursor_y) / tan(angle) + minimap->cursor_x;
	p2->x = (minimap->cursor_x - MINIMAP_SIZE / 15) / minimap->pxl_size;
	if (sin(angle) < 0)
		p2->x = p2->x * minimap->pxl_size - 1;
	else
		p2->x *= minimap->pxl_size + 1;
	p2->y = minimap->cursor_y + (minimap->cursor_x - p2->x) * tan(angle);
}

t_pos	*raycast(t_minimap *minimap, double angle, int **map, t_pos *result)
{
	t_pos	p1;
	t_pos	p2;
	int		dst1;
	int		dst2;

	set_nearest(minimap, &p1, &p2, angle);
	horizontal_wall(minimap, map, &p1, angle);
	vertical_wall(minimap, map, &p2, angle);
	dst1 = ft_abs(p1.x - minimap->cursor_x) + ft_abs(p1.y - minimap->cursor_y);
	dst2 = ft_abs(p2.x - minimap->cursor_x) + ft_abs(p2.y - minimap->cursor_y);
	if (dst1 > dst2)
		*result = p2;
	else
		*result = p1;
	return (result);
}
