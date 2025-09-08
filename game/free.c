/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:56:08 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/08 22:30:50 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	mouse_hook(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		open_close_door(data);
	return (0);
}

void	free_minimap(t_data *data, t_minimap *minimap)
{
	free_image(minimap->minimap, data->display);
	free_image(minimap->cursor, data->display);
	free_image(minimap->direction, data->display);
	free_image(minimap->raycasting, data->display);
	free(minimap);
}

void	free_data(t_data *data)
{
	if (data->mmap)
		free_minimap(data, data->mmap);
	if (data->sc_mmap)
		free_minimap(data, data->sc_mmap);
	free_image(data->background, data->display);
	free_image(data->image, data->display);
	free_image(data->pv, data->display);
	free_crosshair(data);
	free_textures(data);
	if (data->display && data->window)
		mlx_destroy_window(data->display, data->window);
	if (data->display)
	{
		mlx_destroy_display(data->display);
		free(data->display);
	}
	if (data->map)
		free_map(data->map);
}
