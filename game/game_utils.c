/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:33:29 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/08 16:23:07 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	init_textures(t_data *data)
{
	data->texture_n = malloc(sizeof(t_image));
	if (!data->texture_n)
		return (1);
	data->texture_s = malloc(sizeof(t_image));
	if (!data->texture_s)
		return (free(data->texture_n), 1);
	data->texture_e = malloc(sizeof(t_image));
	if (!data->texture_e)
		return (free(data->texture_n), free(data->texture_s), 1);
	data->texture_w = malloc(sizeof(t_image));
	if (!data->texture_w)
		return (free(data->texture_n), free(data->texture_s), \
				free(data->texture_e), 1);
	data->texture_door = malloc(sizeof(t_image));
	if (!data->texture_door)
		return (free(data->texture_n), free(data->texture_s), \
				free(data->texture_e), free(data->texture_w), 1);
	return (0);
}

int	close_window(t_data *data)
{
	cub_exit(0, "Window closed successfully", data);
	return (0);
}

void	free_data(t_data *data)
{
	if (data->mmap)
	{
		free_image(data->mmap->minimap, data->display);
		free_image(data->mmap->cursor, data->display);
		free_image(data->mmap->direction, data->display);
		free_image(data->mmap->raycasting, data->display);
		free(data->mmap);
	}
	if (data->sc_mmap)
	{
		free_image(data->sc_mmap->minimap, data->display);
		free_image(data->sc_mmap->cursor, data->display);
		free_image(data->sc_mmap->direction, data->display);
		free_image(data->sc_mmap->raycasting, data->display);
		free(data->sc_mmap);
	}
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

void	cub_exit(int err, char *str, t_data *data)
{
	ft_printf_fd(2, "cub92i: %s\n", str);
	if (data)
		free_data(data);
	exit(err);
}

__uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((__uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}
