/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:33:29 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/13 19:40:20 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_data(t_data *data)
{
	if (data->minimap)
	{
		free_image(data->minimap->minimap, data->display);
		free_image(data->minimap->cursor, data->display);
		free_image(data->minimap->direction, data->display);
		free_image(data->minimap->raycasting, data->display);
		free(data->minimap);
	}
	free_image(data->background, data->display);
	free_image(data->image, data->display);
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

void	cub_exit(int err, char *str, t_data *data)
{
	ft_printf_fd(2, "cub92i: %s\n", str);
	if (data)
		free_data(data);
	exit(err);
}
