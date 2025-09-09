/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:10 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/09 21:29:31 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_data_to_null(t_data *data)
{
	data->display = NULL;
	data->window = NULL;
	data->background = NULL;
	data->image = NULL;
	data->pv = NULL;
	data->health = 0;
	data->puff = 0;
	data->map = 0;
	data->mmap = 0;
	data->sc_mmap = 0;
	data->raycast = 0;
	data->texture_n = 0;
	data->texture_s = 0;
	data->texture_e = 0;
	data->texture_w = 0;
	data->texture_door = 0;
	data->crosshair = 0;
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;

	if (ac != 2)
		cub_exit(2, "too many arguments\nUsage : ./cub3d <map>", NULL);
	set_data_to_null(&data);
	if (parsing(av[1], &map))
		return (1);
	game(&data, &map);
}
