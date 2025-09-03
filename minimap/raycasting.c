/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:59:29 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/20 17:47:39 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minimap.h"

void	pixel_put(t_image *raycasting, t_pos pixel, int color)
{
	char	*pxl;
	int		b;

	b = raycasting->bpp;
	if (pixel.x >= 0 && pixel.x <= raycasting->tab_x && pixel.y >= 0 && pixel.y <= raycasting->tab_y)
	{
		pxl = raycasting->adress + (pixel.y * raycasting->l_len + pixel.x * (b / 8));
		*(unsigned int *)pxl = color;
	}
}

void	small_angle(t_image *raycasting, t_pos pixel, int dx, int dy)
{
	int	i;
	int	decision;

	i = 0;
	decision = 2 * ft_abs(dy) - ft_abs(dx);
	pixel_put(raycasting, pixel, 11111111);
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
		pixel_put(raycasting, pixel, 11111111);
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

int get_pixel_color(t_image *texture, int x, int y)
{
	int bpp;
	int offset;
	unsigned int *pixel;
	char *addr;

	if (x < 0) 
		x = 0;
    if (x >= texture->tab_x) 
		x = texture->tab_x - 1;
    if (y < 0)
	 	y = 0;
    if (y >= texture->tab_y)
		y = texture->tab_y - 1;
	bpp = texture->bpp / 8;
	offset = y * texture->l_len + x * bpp;
	addr = texture->adress;
	pixel = (unsigned int *)(addr + offset);
	return (*pixel);
}

void	test(t_data *data, t_ray *ray, int i)
{
	t_pos	pixel;
	float	hauteur;
	int		j;
	t_image	*texture;
	int		start;
	int		tex_y;
	int		tex_x;
	float	invert_hauteur;

	pixel.x = i;
	if (ray->dst <= 0)
		ray->dst = 1;	
	hauteur = TAB_Y * (MINIMAP_SIZE / 20) / ray->dst ;
	if (hauteur < 0)
		hauteur = 0;
	if (ray->x_y == 1)
	{
		if (sin(ray->angle) > 0)
			texture = data->texture_s;
		else
			texture = data->texture_n;
	}	
	else
	{
		if (cos(ray->angle) > 0)
			texture = data->texture_e;
		else
			texture = data->texture_w;
	}
	start = (TAB_Y - hauteur) / 2;
	tex_x = ray->percent * texture->tab_x / 100;
	invert_hauteur = 1 / hauteur;
	while (pixel.x < i + 1)	
	{	
		j = start;
		while (j < TAB_Y && j < start + hauteur)
		{
			pixel.y = j++;
			tex_y = (int)((j - start) * (texture->tab_y) * invert_hauteur);
			pixel_put(data->image, pixel, get_pixel_color(texture, tex_x, tex_y));
			// pixel_put(data->image, pixel, encode_rgb(255, 255, 255));
		}
		pixel.x++;
	}
}

void	put_raycasting(t_minimap *minimap, float fov, int ray_nbr, t_data *data)
{
	float	diff;
	int		i;
	// int		dx;
	// int		dy;
	// t_pos	point_a;
	t_pos	point_b;
	t_ray	ray;
	float	fov_div_2;
	int		point;

	i = 0;
	// int	marge = 5;
	fov = (fov * PI) / 180;
	diff = fov / (ray_nbr - 1);
	fov_div_2 = fov / 2.0;
	point = minimap->pxl_size / 3 - minimap->minimap_size_by_15;
	while (i < ray_nbr)
	{
		ray.angle = minimap->p_angle - fov_div_2 + i * diff;
		// point_a.x = minimap->cursor_x + point;
		// point_a.y = minimap->cursor_y + point;
		if (!raycast(minimap, &ray, data, &point_b))
			i = i - 1 + 1;//gerer tan err
		// dx = point_b.x - point_a.x;
		// dy = point_b.y - point_a.y;
		ray.dst = sqrt(ray.dst) * cos(ray.angle - minimap->p_angle);
		test(data, &ray, i);
		// if (ft_abs(dx) > ft_abs(dy))
			// small_angle(minimap->raycasting, point_a, dx, dy);
		// else
			// big_angle(minimap->raycasting, point_a, dx, dy);
		i++;
	}
}
