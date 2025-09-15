/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:07:59 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/15 16:20:03 by igrousso         ###   ########.fr       */
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

void	item_on_map(t_data *data, int item, float pos, double qlqchose)
{
	t_image *texture;
	t_wall	tmp;
	int start_x;
	int start_y;
	float tmp_bounce;

	if (item == MORDJENE)
		texture = data->texture_mordjene;	
	if (item == PUFF)
		texture = data->texture_puff;
	tmp.hauteur = (((TAB_X / 2.0f) / (float)texture->tab_x) * ((MINIMAP_SIZE / data->scale) / qlqchose)) / 4;
	tmp.draw_w = texture->tab_x * tmp.hauteur;
	tmp.draw_h = texture->tab_y * tmp.hauteur;
	tmp_bounce = data->bounce_y * tmp.draw_h / 200.0 ;
	start_x = TAB_X * pos / 100 - (tmp.draw_w / 2);
	start_y = TAB_Y / 2 + tmp_bounce;
	tmp.dx = -1;
	while (++(tmp.dx) < tmp.draw_w)
	{
		tmp.dy = -1;
		while (++(tmp.dy) < tmp.draw_h)
		{
			tmp.tex_x = tmp.dx / tmp.hauteur;
			tmp.tex_y = tmp.dy / tmp.hauteur;
			tmp.pixel.x = start_x + tmp.dx;
			tmp.pixel.y = start_y + tmp.dy;
			if (tmp.pixel.x < 0 || tmp.pixel.x >= TAB_X || tmp.pixel.y < 0 || tmp.pixel.y >= TAB_Y)
				continue;
			int color = get_pixel_color(texture, tmp.tex_x, tmp.tex_y);
			if (color == (int)0xFF000000)
				continue;
			pixel_put(data->image, tmp.pixel, color);
		}
	}
}

void	item_raycast(t_data *d, t_pos pos, double fov, int item)
{
	t_pos	origin;
	float	tmp;
	float	rel_angle;
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
	rel_angle = atan2(is_fov.y, is_fov.x) - d->mmap->p_angle;
	while (rel_angle < -PI)
		rel_angle += 2 * PI;
	while (rel_angle > PI)
		rel_angle -= 2 * PI;
	item_on_map(d, item, (rel_angle + fov) / (2 * fov) * 100, sqrt(pow(dst.x, 2) + pow(dst.y, 2)));
}
