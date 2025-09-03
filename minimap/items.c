/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:06 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/20 16:54:41 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	put_pxl(t_image *image, int x, int y, unsigned int color)
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
	t_pos	id;
	t_pos	c;
	int		draw;
	t_pos	dst;

	c.x = pos.x * minimap->pxl_size + minimap->pxl_size / 2;
	c.y = pos.y * minimap->pxl_size + minimap->pxl_size / 2 + (width / 3);
	id.y = -height / 2 - (width / 3);
	while (id.y <= height / 2)
	{
		id.x = -width / 2;
		while (id.x <= width / 2)
		{
			draw = 0;
			if (id.y >= -height / 2 && id.y <= height / 6)
				draw = 1;
			if (id.y >= -height / 2 - (width / 3) && id.y <= -height / 2
				&& id.x >= -(width / 3) / 2 && id.x <= (width / 3) / 2)
				draw = 1;
			if (id.y >= height / 8)
			{
				dst.x = ft_abs(id.x);
				dst.y = id.y - height / 6;
				if (dst.x * dst.x + dst.y * dst.y <= (width / 2) * (width / 2))
					draw = 1;
			}
			if (draw)
				put_pxl(minimap->minimap, c.x + id.x, c.y + id.y, PUFF_COLOR);
			id.x++;
		}
		id.y++;
	}
}

void	put_mordjene(t_minimap *minimap, t_pos pos, int radius, int inner_radius)
{
	int		dst;
	t_pos	index;
	int		x_diff;
	int		y_diff;

	index.y = -radius;
	x_diff = pos.x * minimap->pxl_size + minimap->pxl_size / 2;
	y_diff = pos.y * minimap->pxl_size + minimap->pxl_size / 2;
	while (index.y <= radius)
	{
		index.x = -radius;
		while (index.x <= radius)
		{
			dst = ft_abs(index.x) + ft_abs(index.y);
			if (dst <= radius)
			{
				if (dst <= inner_radius)
					put_pxl(minimap->minimap, index.x + x_diff, index.y + y_diff, MORDJENE_COLOR);
				else
					put_pxl(minimap->minimap, index.x + x_diff, index.y + y_diff, MORDJENE_BG_COLOR);
			}
			index.x++;
		}
		index.y++;
	}
}
