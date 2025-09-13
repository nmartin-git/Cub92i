/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:33:29 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/13 21:51:23 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	init_textures(t_data *data)
{
	data->texture_n = ft_calloc(sizeof(t_image), 1);
	if (!data->texture_n)
		return (1);
	data->texture_s = ft_calloc(sizeof(t_image), 1);
	if (!data->texture_s)
		return (free(data->texture_n), 1);
	data->texture_e = ft_calloc(sizeof(t_image), 1);
	if (!data->texture_e)
		return (free(data->texture_n), free(data->texture_s), 1);
	data->texture_w = ft_calloc(sizeof(t_image), 1);
	if (!data->texture_w)
		return (free(data->texture_n), free(data->texture_s), \
				free(data->texture_e), 1);
	if (data->map->doors)
	{
		data->texture_door = ft_calloc(sizeof(t_image), 1);
		if (!data->texture_door)
			return (free(data->texture_n), free(data->texture_s), \
					free(data->texture_e), free(data->texture_w), 1);
	}
	else
		data->texture_door = NULL;
	return (0);
}

int	close_window(t_data *data)
{
	cub_exit(0, "Window closed successfully", data);
	return (0);
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

void	set_image_to_null(t_data *data)
{
	data->background->image = NULL;
	data->texture_n->image = NULL;
	data->texture_s->image = NULL;
	data->texture_e->image = NULL;
	data->texture_w->image = NULL;
	if (data->map->doors)
		data->texture_door->image = NULL;
	data->pv = NULL;
}
