/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:33:29 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/15 11:24:26 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	init_textures2(t_data *data)
{
	if (data->map->el_mordjene)
	{
		data->texture_mordjene = ft_calloc(sizeof(t_image), 1);
		if (!data->texture_mordjene)
			return (free(data->texture_n), free(data->texture_s), \
					free(data->texture_e), free(data->texture_w), \
					free(data->texture_door), 1);
	}
	else
		data->texture_mordjene = NULL;
	if (data->map->puff)
	{
		data->texture_puff = ft_calloc(sizeof(t_image), 1);
		if (!data->texture_puff)
			return (free(data->texture_n), free(data->texture_s), \
					free(data->texture_e), free(data->texture_w), \
					free(data->texture_door), free(data->texture_mordjene), 1);
	}
	else
		data->texture_puff = NULL;
	return (0);
}

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
	return (init_textures2(data));
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
	if (data->map->el_mordjene)
		data->texture_mordjene->image = NULL;
	if (data->map->puff)
		data->texture_puff->image = NULL;
	data->pv = NULL;
}
