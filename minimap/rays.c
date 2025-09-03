/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/20 18:06:17 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

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

// int	is_inside_wall(t_minimap *minimap, t_pos *pos)
// {
// 	int	x;
// 	int	y;

// 	x = pos->x/* - MINIMAP_SIZE / 15*/;
// 	y = pos->y/* - MINIMAP_SIZE / 15*/;
// 	// printf("%d, %d\n", x, y);
// 	if (x > minimap->minimap->tab_x || y > minimap->minimap->tab_y)
// 		return (1);
// 	if (get_pixel_img(minimap->minimap, x, y) == minimap->w_color)
// 		return (1);
// 	else
// 		return (0);
// }

void	vertical_wall(t_minimap *minimap, t_data *d, t_pos *pos, double angle)
{
	double	n_tan;
	double	x_off;
	double	y_off;
	double	rx;
	double	ry;
	int		map_x;
	int		map_y;
	int		depth_of_field;

	angle = normalize_angle(angle);
	depth_of_field = 0;
	n_tan = -tan(angle);
	
	// Looking left
	if (angle > PI / 2 && angle < 3 * PI / 2)
	{
		rx = (((int)(minimap->cursor_x + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) / minimap->pxl_size) * minimap->pxl_size) - 1 + MINIMAP_SIZE / 15;
		ry = (minimap->cursor_x + minimap->pxl_size / 3 - rx) * n_tan + minimap->cursor_y + minimap->pxl_size / 3;
		x_off = -minimap->pxl_size;
		y_off = -x_off * n_tan;
	}
	// Looking right
	else if ((angle >= 0 && angle < PI / 2) || (angle > 3 * PI / 2 && angle < 2 * PI))
	{
		rx = (((int)(minimap->cursor_x + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) / minimap->pxl_size) * minimap->pxl_size) + minimap->pxl_size + MINIMAP_SIZE / 15;
		ry = (minimap->cursor_x + minimap->pxl_size / 3 - rx) * n_tan + minimap->cursor_y + minimap->pxl_size / 3;
		x_off = minimap->pxl_size;
		y_off = -x_off * n_tan;
	}
	// Looking straight up or down
	else
	{
		tan_err(pos);
		return ;
	}

	while (depth_of_field < d->map->col)
	{
		map_x = (int)(rx - MINIMAP_SIZE / 15) / minimap->pxl_size;
		map_y = (int)(ry - MINIMAP_SIZE / 15) / minimap->pxl_size;
		
		// Hit a wall or out of bounds
		if (map_x >= 0 && map_x < d->map->col && map_y >= 0 && map_y < d->map->row 
			&& d->map->map[map_y][map_x] == WALL)
		{
			pos->x = (int)rx;
			pos->y = (int)ry;
			return ;
		}
		// Out of bounds
		else if (map_x < 0 || map_x >= d->map->col || map_y < 0 || map_y >= d->map->row)
		{
			tan_err(pos);
			return ;
		}
		// Continue the ray
		else
		{
			rx += x_off;
			ry += y_off;
			depth_of_field++;
		}
	}
	tan_err(pos);
}

void	horizontal_wall(t_minimap *minimap, t_data *d, t_pos *pos, double angle)
{
	double	a_tan;
	double	x_off;
	double	y_off;
	double	rx;
	double	ry;
	int		map_x;
	int		map_y;
	int		depth_of_field;

	angle = normalize_angle(angle);
	depth_of_field = 0;
	a_tan = -1 / tan(angle);
	
	// Looking up
	if (angle > PI)
	{
		ry = (((int)(minimap->cursor_y + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) / minimap->pxl_size) * minimap->pxl_size) - 1 + MINIMAP_SIZE / 15;
		rx = (minimap->cursor_y + minimap->pxl_size / 3 - ry) * a_tan + minimap->cursor_x + minimap->pxl_size / 3;
		y_off = -minimap->pxl_size;
		x_off = -y_off * a_tan;
	}
	// Looking down
	else if (angle < PI && angle != 0)
	{
		ry = (((int)(minimap->cursor_y + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) / minimap->pxl_size) * minimap->pxl_size) + minimap->pxl_size + MINIMAP_SIZE / 15;
		rx = (minimap->cursor_y + minimap->pxl_size / 3 - ry) * a_tan + minimap->cursor_x + minimap->pxl_size / 3;
		y_off = minimap->pxl_size;
		x_off = -y_off * a_tan;
	}
	// Looking straight left or right
	else
	{
		tan_err(pos);
		return ;
	}

	while (depth_of_field < d->map->row)
	{
		map_x = (int)(rx - MINIMAP_SIZE / 15) / minimap->pxl_size;
		map_y = (int)(ry - MINIMAP_SIZE / 15) / minimap->pxl_size;
		
		// Hit a wall or out of bounds
		if (map_x >= 0 && map_x < d->map->col && map_y >= 0 && map_y < d->map->row 
			&& d->map->map[map_y][map_x] == WALL)
		{
			pos->x = (int)rx;
			pos->y = (int)ry;
			return ;
		}
		// Out of bounds
		else if (map_x < 0 || map_x >= d->map->col || map_y < 0 || map_y >= d->map->row)
		{
			tan_err(pos);
			return ;
		}
		// Continue the ray
		else
		{
			rx += x_off;
			ry += y_off;
			depth_of_field++;
		}
	}
	tan_err(pos);
}


t_ray	*raycast(t_minimap *minimap, t_ray *ray, t_data *data, t_pos *result)
{
	t_pos	ph;
	t_pos	pv;
	// t_pos	verif;
	long	dst1;
	long	dst2;
	int		x_origin;
	int		y_origin;

	ray->angle = normalize_angle(ray->angle);
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
