/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:27:20 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/07 20:24:44 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/background.h"

/*
colorie le pixel de la couleur du plafond
*/

void	paint_ceiling(char *dst, t_data *data, int j)
{
	int	r;
	int	g;
	int	b;

	r = decode_r(data->map->c_rgb);
	g = decode_g(data->map->c_rgb);
	b = decode_b(data->map->c_rgb);
	if (r != 0)
		r = r - (j / (1080 / r));
	if (g != 0)
		g = g - (j / (1080 / g));
	if (b != 0)
		b = b - (j / (1080 / b));
	*(unsigned int *)dst = encode_rgb(r, g, b);
}

/*
colorie le pixel de la couleur du sol
*/

void	paint_floor(char *dst, t_data *data, int j)
{
	int	r;
	int	g;
	int	b;

	r = decode_r(data->map->f_rgb);
	g = decode_g(data->map->f_rgb);
	b = decode_b(data->map->f_rgb);
	if (r != 0)
		r = r - ((1080 - j) / (1080 / r));
	if (g != 0)
		g = g - ((1080 - j) / (1080 / g));
	if (b != 0)
		b = b - ((1080 - j) / (1080 / b));
	*(unsigned int *)dst = encode_rgb(r, g, b);
}

/*
parcourt la ligne
*/

void	gateway_paint(char *dst, t_image *img, t_data *data, int i)
{
	int	j;

	j = -1;
	while (++j < 1080)
	{
		dst = img->adress + (j * img->l_len + i * (img->bpp / 8));
		if (j < 1080 / 2)
			paint_ceiling(dst, data, j);
		else
			paint_floor(dst, data, j);
	}
}

/*
contruit l'image du background
*/

int	paint_floor_and_ceiling(t_image *img, t_data *data)
{
	int		i;
	char	*dst;
	int		easter_egg;

	img->image = mlx_new_image(data->display, 1920, 1080);
	if (!img->image)
		return (destroy_img(img, data), write(2,
				"Error\nFail to create image\n", 27));
	img->adress = mlx_get_data_addr(img->image, &img->bpp, &img->l_len, NULL);
	if (!img->adress)
		return (destroy_img(img, data), write(2,
				"Error\nFail to get image address\n", 32));
	i = -1;
	while (++i < 1920)
		gateway_paint(dst, img, data, i);
	return (0);
}
