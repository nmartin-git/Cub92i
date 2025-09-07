/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:41:33 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/07 19:15:31 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/background.h"

void	put_pixel_img(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000 || !color)
		return ;
	if (x >= 0 && y >= 0 && x < img->tab_x && y < img->tab_y)
	{
		dst = img->adress + (y * img->l_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

unsigned int	get_pixel_img(t_image *img, int x, int y)
{
	return (*(unsigned int *)((img->adress + (y * img->l_len) + \
			(x * img->bpp / 8))));
}

void	put_img_to_img(t_image *dst, t_image *src, int x_offset, int y_offset)
{
	unsigned int	px;
	t_tmp			t;

	t.s_len = src->tab_x;
	t.d_len = dst->tab_x;
	if (!dst || !src || !dst->adress || !src->adress)
		return ;
	if (x_offset < 0 || y_offset < 0)
		return ;
	t.y = -1;
	while (++t.y < src->tab_y)
	{
		if (t.y + y_offset >= dst->tab_y)
			break ;
		t.x = -1;
		while (++t.x < src->tab_x)
		{
			if (t.x + x_offset >= dst->tab_x)
				break ;
			px = ((int *)src->adress)[t.y * t.s_len + t.x];
			if (px != 0)
				((int *)dst->adress)[(t.y + y_offset) * t.d_len + \
					(t.x + x_offset)] = px;
		}
	}
}
