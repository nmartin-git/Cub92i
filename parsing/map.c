/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:42:56 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/07 16:47:26 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

/*
remplie une ligne de la map
*/

int	fill_row(int **row, char *line, int col, int *count_spawn)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 1;
	(*row)[0] = 8;
	while (i < (col + 2))
	{
		if (i <= len)
		{
			(*row)[i] = ctoi(line[i - 1], count_spawn);
			if ((*row)[i] == -2)
				return (free(line), 1);
			if (count_spawn < 0)
				return (free(line), write(2, "Error\n \
                    Map contains duplicates\n", 30));
		}
		else
			(*row)[i] = 8;
		i++;
	}
	(*row)[i] = 9;
	return (free(line), 0);
}

/*
initialise la map et rempli la premiere ligne d'espaces vides
*/

int	init_map(t_map *map, int fd, char *av)
{
	int	i;

	i = -1;
	map->row = count_size(fd, &map->col);
	if (map->row < 1)
		return (1);
	map->map = ft_calloc((map->row + 3), sizeof(int *));
	if (!(map->map))
		return (write(2, "Error\nMalloc map fail\n", 22));
	close(fd);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (free(map->map), write(2, "Error\nOpen fail\n", 28));
	map->map[0] = ft_calloc((map->col + 3), sizeof(int));
	if (!(map->map[0]))
		return (ft_free_tab_int(map->map), write(2, "Error\n \
                                                Malloc fail\n", 22));
	while (++i < (map->col + 2))
		map->map[0][i] = 8;
	map->map[0][i] = 9;
	return (0);
}

/*
rempli la dernière ligne d'espaces vides
*/

int	last_row(int **row, int col)
{
	int	i;

	i = -1;
	(*row) = ft_calloc((col + 3), sizeof(int));
	if (!(*row))
		return (write(2, "Error\nMalloc map fail\n", 22));
	while (++i < (col + 2))
		(*row)[i] = 8;
	(*row)[i] = 9;
	return (0);
}

/*
va créer la map dans un double tableau int
*/

int	fill_tabmap(int fd, t_map *map, int *i)
{
	char	*line;
	int		is_empty;
	int		count_spawn;

	count_spawn = 1;
	if (start_of_map(fd, &line))
		return (1);
	while ((*i) < (map->row + 1))
	{
		map->map[(*i)] = ft_calloc((map->col + 3), sizeof(int));
		if (!(map->map[(*i)]))
			return (ft_free_tab_int(map->map), free(line), \
				write(2, "Error\nMalloc map fail\n", 22));
		if (fill_row(&(map->map[(*i)]), line, map->col, &count_spawn))
			return (ft_free_tab_int(map->map), 1);
		line = get_next_line(fd, &is_empty);
		if (!line && !is_empty)
			return (ft_free_tab_int(map->map), \
				write(2, "Error\nget_next_line fill_tabmap error\n", 38));
		(*i)++;
	}
	if (count_spawn)
		return (ft_free_tab_int(map->map), \
			write(2, "Error\nMissing spawn point\n", 26));
	return (0);
}

void	set_pos_spawn(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j] != 9)
		{
			if (map->map[i][j] >= 2 && map->map[i][j] <= 5)
			{
				map->x_spawn = j;
				map->y_spawn = i;
				return ;
			}
			j++;
		}
		i++;
	}
}
