/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:10 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/05 14:36:31 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;
	
	(void)av;
	if (ac != 2)
		cub_exit(2, "too many arguments\nUsage : ./cub3d <map>", NULL);
	parsing(av[1], &map);
	game(&data, &map);
}
