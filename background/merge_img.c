/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:41:33 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/13 01:44:23 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/background.h"

/*
colorie le pixel dans la nouvelle image
*/

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

/*
renvoie la couleur du pixel
*/

unsigned int	get_pixel_img(t_image *img, int x, int y)
{
	return (*(unsigned int *)((img->adress + (y * img->l_len) + (x * img->bpp
					/ 8))));
}

/*
place une image au dessus d'une autre sans prendre en compte
les pixels vides
*/

// void	put_img_to_img(t_image *dst, t_image *src, int x, int y)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (!dst || !src || !dst->adress || !src->adress)
// 		return ;
// 	while (i < src->tab_y)
// 	{
// 		j = 0;
// 		while (j < src->tab_x)
// 		{
// 			put_pixel_img(dst, x + j, y + i, get_pixel_img(src, j, i));
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	put_img_to_img(t_image *dst, t_image *src, int x_offset, int y_offset)
{
	unsigned int	px;
	int				s_len;
	int				d_len;
	int				x;
	int				y;

	s_len = src->tab_x;
	d_len = dst->tab_x;
	if (!dst || !src || !dst->adress || !src->adress)
		return ;
	if (x_offset < 0 || y_offset < 0)
		return ;
	y = -1;
	while (++y < src->tab_y)
	{
		if (y + y_offset >= dst->tab_y)
			break ;
		x = 0;
		while (++x < src->tab_x)
		{
			if (x + x_offset >= dst->tab_x)
				break ;
			px = ((int *)src->adress)[y * s_len + x];
			if (px != 0)
				((int *)dst->adress)[(y + y_offset) * d_len + (x
						+ x_offset)] = px;
		}
	}
}
