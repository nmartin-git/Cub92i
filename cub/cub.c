/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:10 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/02 15:24:07 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	fdf_exit(int err, char *str, t_data *data)
{
	ft_printf_fd(2, "cub3d: %s\n", str);
	if (data)
		fdf_free(err, data);
	exit(err);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		fdf_exit(2, "too many arguments\nUsage : ./cub3d <map>", NULL);
	//parsing(av[1]);
	game(&data);
}
