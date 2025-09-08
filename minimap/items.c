/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:06 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/09 00:46:32 by igrousso         ###   ########.fr       */
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

void	put_puff2(t_tmp3 *t, int width, int height, t_minimap *minimap)
{
	t->draw = 0;
	if (t->id.y >= -height / 2 && t->id.y <= height / 6)
		t->draw = 1;
	if (t->id.y >= -height / 2 - (width / 3) && t->id.y <= -height / 2
		&& t->id.x >= -(width / 3) / 2 && t->id.x <= (width / 3) / 2)
		t->draw = 1;
	if (t->id.y >= height / 8)
	{
		t->dst.x = ft_abs(t->id.x);
		t->dst.y = t->id.y - height / 6;
		if (t->dst.x * t->dst.x + t->dst.y * t->dst.y <= (width / 2) * \
			(width / 2))
			t->draw = 1;
	}
	if (t->draw)
		put_pxl(minimap->minimap, t->c.x + t->id.x, t->c.y + t->id.y, \
			PUFF_COLOR);
}

void	put_puff(t_minimap *minimap, t_pos pos, int width, int height)
{
	t_tmp3	t;

	t.c.x = pos.x * minimap->pxl_size + minimap->pxl_size / 2;
	t.c.y = pos.y * minimap->pxl_size + minimap->pxl_size / 2 + (width / 3);
	t.id.y = -height / 2 - (width / 3);
	while (t.id.y <= height / 2)
	{
		t.id.x = -width / 2;
		while (t.id.x <= width / 2)
		{
			put_puff2(&t, width, height, minimap);
			t.id.x++;
		}
		t.id.y++;
	}
}

void	put_mordjene(t_minimap *minimap, t_pos pos, int radius, int Iradius)
{
	int		dst;
	t_pos	index;
	int		x_diff;
	int		y_diff;

	index.y = -radius - 1;
	x_diff = pos.x * minimap->pxl_size + minimap->pxl_size / 2;
	y_diff = pos.y * minimap->pxl_size + minimap->pxl_size / 2;
	while (++index.y <= radius)
	{
		index.x = -radius - 1;
		while (++index.x <= radius)
		{
			dst = ft_abs(index.x) + ft_abs(index.y);
			if (dst <= radius)
			{
				if (dst <= Iradius)
					put_pxl(minimap->minimap, index.x + x_diff, index.y \
						+ y_diff, MORDJENE_COLOR);
				else
					put_pxl(minimap->minimap, index.x + x_diff, index.y \
						+ y_diff, MORDJENE_BG_COLOR);
			}
		}
	}
}
