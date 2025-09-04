/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:10 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/04 19:56:53 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;

	if (ac != 2)
		cub_exit(2, "too many arguments\nUsage : ./cub3d <map>", NULL);
	if (parsing(av[1], &map))
		return (1);
	game(&data, &map);
}
