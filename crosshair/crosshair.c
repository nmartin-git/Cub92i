/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:15:18 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/16 18:04:10 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crosshair.h"

void	vertical_crosshair(t_crosshair *crosshair, int color)
{
	int		i;
	int		j;
	int		k;
	t_pos	pixel;

	k = -1;
	pixel.y = 1;
	while (++k < 2)
	{
		j = -1;
		while (++j < LENGHT_C)
		{
			i = -1;
			while (++i < WIDTH_C)
			{
				pixel.x = crosshair->img_size / 2 - WIDTH_C / 2 + i;
				pixel_put(crosshair->cross_img, pixel, color);
			}
			pixel.y++;
		}
		pixel.y += GAP_C;
	}
}

void	horizontal_crosshair(t_crosshair *crosshair, int color)
{
	int		i;
	int		j;
	int		k;
	t_pos	pixel;

	k = -1;
	pixel.x = 1;
	while (++k < 2)
	{
		j = -1;
		while (++j < LENGHT_C)
		{
			i = -1;
			while (++i < WIDTH_C)
			{
				pixel.y = crosshair->img_size / 2 - WIDTH_C / 2 + i;
				pixel_put(crosshair->cross_img, pixel, color);
			}
			pixel.x++;
		}
		pixel.x += GAP_C;
	}
}

int	init_crosshair(t_data *data)
{
	t_image		*cross_img;
	t_crosshair	*crosshair;
	int			color;

	crosshair = malloc(sizeof(t_crosshair));
	if (!crosshair)
		return (1);
	crosshair->img_size = LENGHT_C * 2 + GAP_C + 2;
	crosshair->pos_c_x = (TAB_X / 2) - crosshair->img_size / 2;
	crosshair->pos_c_y = (TAB_Y / 2) - crosshair->img_size / 2;
	cross_img = new_image(data->display, crosshair->img_size,
			crosshair->img_size);
	if (!cross_img)
		return (free(crosshair), 1);
	color = CYAN;
	crosshair->cross_img = cross_img;
	vertical_crosshair(crosshair, color);
	horizontal_crosshair(crosshair, color);
	data->crosshair = crosshair;
	return (0);
}

void	free_crosshair(t_data *data)
{
	free_image(data->crosshair->cross_img, data->display);
	free(data->crosshair);
}
