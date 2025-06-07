/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:33:29 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/05 18:36:22 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_data(t_data *data)
{
	if (data->minimap && data->minimap->image)
		mlx_destroy_image(data->display, data->minimap->image);
	if (data->image && data->image)
		mlx_destroy_image(data->display, data->image);
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
