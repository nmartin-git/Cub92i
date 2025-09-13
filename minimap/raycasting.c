/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:59:29 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/13 22:15:58 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	small_angle(t_image *minimap, t_pos pixel, int dx, int dy)
{
	int	i;
	int	decision;

	i = 0;
	decision = 2 * ft_abs(dy) - ft_abs(dx);
	pixel_put(minimap, pixel, 11111111);
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
		pixel_put(minimap, pixel, 11111111);
	}
}

void	big_angle(t_image *raycasting, t_pos pixel, int dx, int dy)
{
	int	i;
	int	decision;

	i = 0;
	decision = 2 * ft_abs(dx) - ft_abs(dy);
	pixel_put(raycasting, pixel, 11111111);
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
		pixel_put(raycasting, pixel, 11111111);
	}
}

void	set_texture(t_data *data, t_image **texture, t_ray *ray, t_wall *tmp)
{
	if (ray->door)
		(*texture) = data->texture_door;
	else if (ray->x_y == 1)
	{
		if (sin(ray->angle) > 0)
		{
			tmp->invert = 1;
			(*texture) = data->texture_s;
		}
		else
			(*texture) = data->texture_n;
	}
	else
	{
		if (cos(ray->angle) > 0)
			(*texture) = data->texture_e;
		else
		{
			tmp->invert = 1;
			(*texture) = data->texture_w;
		}
	}
}

void	draw_wall(t_data *data, t_ray *ray, int i)
{
	t_image	*texture;
	t_wall	tmp;

	tmp.invert = 0;
	tmp.pixel.x = i;
	if (ray->dst <= 0)
		ray->dst = 1;
	tmp.hauteur = TAB_Y * (MINIMAP_SIZE / data->scale) / ray->dst;
	if (tmp.hauteur < 0)
		tmp.hauteur = 0;
	set_texture(data, &texture, ray, &tmp);
	set_order_texture(texture, ray, &tmp);
	while (tmp.j < TAB_Y && tmp.j < tmp.start + tmp.hauteur)
	{
		tmp.pixel.y = tmp.j;
		tmp.tex_y = (int)((tmp.j - tmp.start) * (texture->tab_y) / tmp.hauteur);
		if (tmp.tex_y >= texture->tab_y)
			tmp.tex_y = texture->tab_y - 1;
		if (tmp.tex_y < 0)
			tmp.tex_y = 0;
		pixel_put(data->image, tmp.pixel, get_pixel_color(texture, tmp.tex_x,
				tmp.tex_y));
		(tmp.j)++;
	}
}

void	put_raycasting(t_minimap *minimap, float fov, int ray_nb, t_data *data)
{
	float	diff;
	int		i;
	t_pos	point_b;
	t_ray	ray;
	int		point;

	i = 0;
	fov = (fov * PI) / 180;
	diff = fov / (ray_nb - 1);
	point = minimap->pxl_size / 3 - minimap->sb15;
	while (i < ray_nb)
	{
		ray.angle = minimap->p_angle - fov / 2.0 + i * diff;
		if (!raycast(minimap, &ray, data, &point_b))
			i = i - 1 + 1; // gerer tan err
		ray.dst = sqrt(ray.dst) * cos(ray.angle - minimap->p_angle);
		draw_wall(data, &ray, i);
		i++;
	}
	if (data->map->puff || data->map->el_mordjene)
		set_item_rayscast(data);
}
