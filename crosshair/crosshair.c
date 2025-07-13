/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:15:18 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/13 02:51:52 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crosshair.h"

void	vertical_crosshair(t_image *crosshair, int color)
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
				pixel.x = IMG_SIZE / 2 - WIDTH_C / 2 + i;
				pixel_put(crosshair, pixel, color);
			}
			pixel.y++;
		}
		pixel.y += GAP_C;
	}
}

void	horizontal_crosshair(t_image *crosshair, int color)
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
				pixel.y = IMG_SIZE / 2 - WIDTH_C / 2 + i;
				pixel_put(crosshair, pixel, color);
			}
			pixel.x++;
		}
		pixel.x += GAP_C;
	}
}

int	init_crosshair(t_data *data)
{
	t_image	*crosshair;
	int		color;

	crosshair = new_image(data->display, IMG_SIZE, IMG_SIZE);
	if (!crosshair)
		return (1);
	color = RED;
	vertical_crosshair(crosshair, color);
	horizontal_crosshair(crosshair, color);
	data->crosshair = crosshair;
	return (0);
}
