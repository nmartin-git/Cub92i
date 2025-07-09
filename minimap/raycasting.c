/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:59:29 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/09 17:52:09 by igrousso         ###   ########.fr       */
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

void	test(t_data *data, float distance, int i)
{
	t_pos	pixel;
	float	hauteur;
	int		j;

	pixel.x = i;
	if (distance <= 0)
		distance = 1;	
	hauteur = TAB_Y * (MINIMAP_SIZE / 20) / distance ;
	if (hauteur > TAB_Y)
		hauteur = TAB_Y;
	if (hauteur < 0)
		hauteur = 0;
	while (pixel.x < i + 1)	
	{	
		j = (TAB_Y - hauteur) / 2;
		while (j < ((TAB_Y - hauteur) / 2) + hauteur)
		{
			pixel.y = j++;
			pixel_put(data->game, pixel, encode_rgb(255, 255, 255));
		}
		pixel.x++;
	}
}

void	put_raycasting(t_minimap *minimap, double fov, int ray_nbr, t_data *data)
{
	double	diff;
	int		i;
	int		dx;
	int		dy;
	t_pos	point_a;
	t_pos	point_b;
	t_ray	ray;

	i = 0;
	fov = (fov * PI) / 180;
	diff = fov / (ray_nbr - 1);
	while (i < ray_nbr)
	{
		ray.angle = minimap->p_angle - (fov / 2.0) + i * diff;
		point_a.x = minimap->cursor_x + minimap->pxl_size / 3 - MINIMAP_SIZE / 15;
		point_a.y = minimap->cursor_y + minimap->pxl_size / 3 - MINIMAP_SIZE / 15;
		if (!raycast(minimap, &ray, data, &point_b))
			i = i - 1 + 1;//gerer tan err
		dx = point_b.x - point_a.x;
		dy = point_b.y - point_a.y;
		float distance = sqrt(pow(dx, 2) + pow(dy, 2));
		float distance_corrigée = distance * cos(ray.angle - minimap->p_angle);
		// printf("numero de colonne: %d, ray_angle %f, player_angle %f\n", i, ray.angle, minimap->p_angle);
		// printf("delta_angle %f, ray.angle - p_angle %f, i %d\n", delta_angle, ray.angle - minimap->p_angle, i);
		// if (i < 25 || (i >= 948 && i <= 973) || i > 1895)
			// printf("distance %f, cos %f, distance corrigée %f, hauteur %f, %d\n", distance, cos(delta_angle), distance_corrigée, TAB_Y * (MINIMAP_SIZE / 20) / distance_corrigée, i);		
 		test(data, distance_corrigée, i);
		// if (ft_abs(dx) > ft_abs(dy))
			// small_angle(minimap->raycasting, point_a, dx, dy);
		// else
			// big_angle(minimap->raycasting, point_a, dx, dy);
		i++;
	}
}
