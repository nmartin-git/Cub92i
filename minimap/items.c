/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:06 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/10 17:40:51 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	put_pxl(t_image *image, int x, int y, int color)
{
	char	*pxl;
	int		b;
	int		l;

	b = image->bpp;
	l = image->l_len;
	if (x >= 0 && x <= image->tab_x
		&& y >= 0 && y <= image->tab_y)
	{
		pxl = image->adress + (y * l + x * (b / 8));
		*(unsigned int *)pxl = color;
	}
}

void	put_puff(t_minimap *minimap, t_pos pos, int width, int height)
{
	int	x;
	int	y;
	int	x_center;
	int	y_center;
	int embout_size;
	int	draw;
	int	dx;
	int	dy;
	int	radius_bottom;

	x_center = pos.x * minimap->pxl_size + minimap->pxl_size / 2;
	embout_size = width / 3;
	y_center = pos.y * minimap->pxl_size + minimap->pxl_size / 2 + embout_size;
	y = -height / 2 - embout_size;
	while (y <= height / 2)
	{
		x = -width / 2;
		while (x <= width / 2)
		{
			draw = 0;
			if (y >= -height / 2 && y <= height / 6)
				draw = 1;
			if (y >= -height / 2 - embout_size && y <= -height / 2 && 
				x >= -embout_size / 2 && x <= embout_size / 2)
				draw = 1;
			if (y >= height / 8)
			{
				dx = ft_abs(x);
				dy = y - height / 6;
				radius_bottom = width / 2;
				if (dx * dx + dy * dy <= radius_bottom * radius_bottom)
					draw = 1;
			}
			if (draw)
				put_pxl(minimap->minimap, x_center + x, y_center + y, PUFF_COLOR);
			x++;
		}
		y++;
	}
}

void	put_mordjene(t_minimap *minimap, t_pos pos, int radius, int inner_radius)
{
	int	dst;
	int	x;
	int	y;
	int	x_diff;
	int	y_diff;

	y = -radius;
	x_diff = pos.x * minimap->pxl_size + minimap->pxl_size / 2;
	y_diff = pos.y * minimap->pxl_size + minimap->pxl_size / 2;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			dst = ft_abs(x) + ft_abs(y);
			if (dst <= radius)
			{
				if (dst <= inner_radius)
					put_pxl(minimap->minimap, x + x_diff, y + y_diff, MORDJENE_COLOR);
				else
					put_pxl(minimap->minimap, x + x_diff, y + y_diff, MORDJENE_BG_COLOR);
			}
			x++;
		}
		y++;
	}
}

// void	is_puff()
// {
	
// }
