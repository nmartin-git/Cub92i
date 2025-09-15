/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:33:29 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/15 14:17:17 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	pixel_put_square(t_minimap *minimap, t_pos pixel, int color)
{
	char	*pxl;
	t_tmp2	t;

	t.b = minimap->minimap->bpp;
	t.l = minimap->minimap->l_len;
	t.x = pixel.x * minimap->pxl_size;
	pixel.y *= minimap->pxl_size;
	t.y = -1;
	while (++t.y < minimap->pxl_size)
	{
		t.i = -1;
		pixel.x = t.x;
		while (++t.i < minimap->pxl_size)
		{
			if (pixel.x >= 0 && pixel.x <= minimap->minimap->tab_x
				&& pixel.y >= 0 && pixel.y <= minimap->minimap->tab_y)
			{
				pxl = minimap->minimap->adress + (pixel.y * t.l + pixel.x * \
						(t.b / 8));
				*(unsigned int *)pxl = color;
			}
			pixel.x++;
		}
		pixel.y++;
	}
}

int	load_image(t_minimap *minimap, t_data *data)
{
	minimap->minimap = new_image(data->display, minimap->pxl_size * minimap->x,
			minimap->pxl_size * minimap->y);
	if (!minimap->minimap)
		return (1);
	minimap->cursor = new_image(data->display, minimap->pxl_size / 1.5,
			minimap->pxl_size / 1.5);
//TODO gerer la taille du cursuer (propotionnel)
	if (!minimap->cursor)
		return (1);
	minimap->direction = new_image(data->display, minimap->pxl_size * 2,
			minimap->pxl_size * 2);
//TODO gerer la taille du cursuer (propotionnel)
	if (!minimap->direction)
		return (1);
	minimap->raycasting = new_image(data->display, minimap->pxl_size
			* minimap->x, minimap->pxl_size * minimap->y);
//TODO gerer la taille du cursuer (propotionnel)
	if (!minimap->raycasting)
		return (1);
	return (0);
}

void	pixel_put(t_image *raycasting, t_pos pixel, int color)
{
	char	*pxl;
	int		b;

	b = raycasting->bpp;
	if (pixel.x >= 0 && pixel.x <= raycasting->tab_x && pixel.y >= 0 && \
		pixel.y <= raycasting->tab_y)
	{
		pxl = raycasting->adress + (pixel.y * raycasting->l_len + pixel.x * \
			(b / 8));
		*(unsigned int *)pxl = color;
	}
}

int	get_pixel_color(t_image *texture, int x, int y)
{
	int				bpp;
	int				offset;
	unsigned int	*pixel;
	char			*addr;

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

void	set_order_texture(t_image *texture, t_ray *ray, t_wall *tmp)
{
	tmp->tex_x = ray->percent * texture->tab_x / 100;
	if (tmp->invert == 1)
		tmp->tex_x = texture->tab_x - 1 - tmp->tex_x;
	if (tmp->tex_x < 0)
		tmp->tex_x = 0;
	if (tmp->tex_x >= texture->tab_x)
		tmp->tex_x = texture->tab_x - 1;
	tmp->start = (TAB_Y - tmp->hauteur) / 2;
	tmp->j = tmp->start;
}
