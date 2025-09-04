/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:31:38 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/04 17:22:43 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

/*
vérifie si les contours de la map sont bien des murs
*/

int	check_neighbors(t_map *map, int x, int y)
{
	if (y - 1 >= 0 && x - 1 >= 0 && \
		map->map[y - 1][x - 1] != 8 && map->map[y - 1][x - 1] != 1)
		return (write(2, "Error\nInvalid map\n", 18));
	if (y + 1 <= map->row && x - 1 >= 0 && \
		map->map[y + 1][x - 1] != 8 && map->map[y + 1][x - 1] != 1)
		return (write(2, "Error\nInvalid map\n", 18));
	if (y - 1 >= 0 && x + 1 < map->col && \
		map->map[y - 1][x + 1] != 8 && map->map[y - 1][x + 1] != 1)
		return (write(2, "Error\nInvalid map\n", 18));
	if (y + 1 <= map->row && x + 1 < map->col && \
		map->map[y + 1][x + 1] != 8 && map->map[y + 1][x + 1] != 1)
		return (write(2, "Error\nInvalid map\n", 18));
	if (y - 1 >= 0 && map->map[y - 1][x] != 8 && map->map[y - 1][x] != 1)
		return (write(2, "Error\nInvalid map\n", 18));
	if (y + 1 <= map->row && map->map[y + 1][x] != 8 && map->map[y + 1][x] != 1)
		return (write(2, "Error\nInvalid map\n", 18));
	if (x - 1 >= 0 && map->map[y][x - 1] != 8 && map->map[y][x - 1] != 1)
		return (write(2, "Error\nInvalid map\n", 18));
	if (x + 1 < map->col && map->map[y][x + 1] != 8 && map->map[y][x + 1] != 1)
		return (write(2, "Error\nInvalid map\n", 18));
	return (0);
}

/*
vérifie si la map est valide
*/

int	check_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x] != 9)
		{
			if (map->map[y][x] == 10)
				if (check_doors(map, x, y))
					return (write(2, \
						"Error\nDoors must be between walls\n", 34));
			if (map->map[y][x] == 8)
				if (check_neighbors(map, x, y))
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

/*
vérifie si le fichié passé en argument est sous la bonne extension
*/

int	check_av(char *av, int *fd)
{
	size_t	len;

	len = strlen(av);
	if (len < 4 || \
		(av[len - 4] != '.' && \
		av[len - 3] != 'c' && \
		av[len - 2] != 'u' && \
		av[len - 1] != 'b'))
		return (write(2, "Error\nThe file is not a .cub file\n", 34));
	*fd = open(av, O_RDONLY);
	if ((*fd) < 0)
		return (write(2, "Error\nFailed to open the file\n", 30));
	return (0);
}

/*
vérifie si il manque des informations poru la map
*/

int	check_infos(t_map *map)
{
	if (!map->n_t)
		return (write(2, "Error\nMissing information for north\n", 36));
	if (!map->s_t)
		return (write(2, "Error\nMissing information for south\n", 36));
	if (!map->e_t)
		return (write(2, "Error\nMissing information for east\n", 35));
	if (!map->w_t)
		return (write(2, "Error\nMissing information for weast\n", 36));
	if (!map->f_rgb)
		return (write(2, "Error\nMissing information for floor\n", 40));
	if (!map->c_rgb)
		return (write(2, "Error\nMissing information for ceiling\n", 38));
	return (0);
}

/*
verifie si les rgb envoyés sont bien des chiffres
*/

int	check_colors(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j++]))
				return (1);
		}
		i++;
	}
	return (0);
}
