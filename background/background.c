/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:27:20 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/16 17:04:40 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/background.h"
#include "../headers/game.h"

void	paint_ceiling(char *dst, t_data *data, int j)
{
	int	r;
	int	g;
	int	b;

	r = decode_r(data->map->c_rgb);
	g = decode_g(data->map->c_rgb);
	b = decode_b(data->map->c_rgb);
	if (r != 0)
		r = r - (j / (TAB_Y / r));
	if (g != 0)
		g = g - (j / (TAB_Y / g));
	if (b != 0)
		b = b - (j / (TAB_Y / b));
	*(unsigned int *)dst = encode_rgb(r, g, b);
}

void	paint_floor(char *dst, t_data *data, int j)
{
	int	r;
	int	g;
	int	b;

	r = decode_r(data->map->f_rgb);
	g = decode_g(data->map->f_rgb);
	b = decode_b(data->map->f_rgb);
	if (r != 0)
		r = r - ((TAB_Y - j) / (TAB_Y / r));
	if (g != 0)
		g = g - ((TAB_Y - j) / (TAB_Y / g));
	if (b != 0)
		b = b - ((TAB_Y - j) / (TAB_Y / b));
	*(unsigned int *)dst = encode_rgb(r, g, b);
}

void	gateway_paint(char *dst, t_image *img, t_data *data, int i)
{
	int	j;

	j = -1;
	while (++j < TAB_Y)
	{
		dst = img->adress + (j * img->l_len + i * (img->bpp / 8));
		if (data->map->c_rgb > 0 && j < TAB_Y / 2)
			paint_ceiling(dst, data, j);
		else if (data->map->f_rgb > 0 && j >= TAB_Y / 2)
			paint_floor(dst, data, j);
	}
}

int	paint_floor_and_ceiling(t_image *img, t_data *data)
{
	int		i;
	char	*dst;
	int		null;

	dst = NULL;
	init_image(img);
	img->image = mlx_new_image(data->display, TAB_X, TAB_Y);
	if (!img->image)
		return (mlx_destroy_image(data->display, img->image), write(2,
				"Error\nFail to create image\n", 27));
	img->tab_x = TAB_X;
	img->tab_y = TAB_Y;
	img->adress = mlx_get_data_addr(img->image, &img->bpp, &img->l_len, &null);
	if (!img->adress)
		return (mlx_destroy_image(data->display, img->image), write(2,
				"Error\nFail to get image address\n", 32));
	i = -1;
	if (data->map->c_rgb <= -10)
		if (easter_egg(img, data))
			return (mlx_destroy_image(data->display, img->image), 1);
	while (++i < TAB_X)
		gateway_paint(dst, img, data, i);
	return (0);
}
