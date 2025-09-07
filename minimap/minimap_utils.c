/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:33:29 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/07 21:58:28 by igrousso         ###   ########.fr       */
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
