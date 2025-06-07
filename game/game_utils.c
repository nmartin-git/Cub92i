/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:33:29 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/06 17:04:13 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_data(t_data *data)
{
	if (data->minimap)
	{
		freeImage(data->minimap->minimap, data->display);
		freeImage(data->minimap->cursor, data->display);
	}
	if (data->image)
		freeImage(data->image, data->display);
	if (data->display && data->window)
		mlx_destroy_window(data->display, data->window);
	if (data->display)
	{
		mlx_destroy_display(data->display);
		free(data->display);
	}
	if (data->map)
		free_map(data->map);
	if (data->minimap)
		free(data->minimap);
}

void	cub_exit(int err, char *str, t_data *data)
{
	ft_printf_fd(2, "cub3d: %s\n", str);
	if (data)
		free_data(data);
	exit(err);
}
