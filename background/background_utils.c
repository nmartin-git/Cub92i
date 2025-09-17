/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:20:25 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/17 16:36:24 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/background.h"

int	decode_r(int rgb)
{
	return ((rgb >> 16) & 255);
}

int	decode_g(int rgb)
{
	return ((rgb >> 8) & 255);
}

int	decode_b(int rgb)
{
	return (rgb & 255);
}

void	init_image(t_image *img)
{
	img->image = NULL;
	img->adress = NULL;
	img->bpp = -1;
	img->l_len = -1;
	img->tab_x = -1;
	img->tab_y = -1;
}

int	get_adress(t_data *data, t_image *new, t_image *new2)
{
	int	null;

	new->adress = mlx_get_data_addr(new->image, &new->bpp, &new->l_len, &null);
	if (!new->adress)
	{
		mlx_destroy_image(data->display, new->image);
		return (mlx_destroy_image(data->display, new->image),
			write(2, "Error\nFail to init\n", 19));
	}
	if (data->map->f_rgb == -10)
	{
		new2->adress = mlx_get_data_addr(new2->image, &new2->bpp,
				&new2->l_len, &null);
		if (!new2->adress)
		{
			mlx_destroy_image(data->display, new2->image);
			return (mlx_destroy_image(data->display, new->image),
				mlx_destroy_image(data->display, new->image),
				write(2, "Error\nFail to init\n", 19));
		}
	}
	return (0);
}
