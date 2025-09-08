/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:35 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/08 16:38:41 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

int	fill_infos(int fd, t_map *map)
{
	char	*line;
	int		count;
	int		is_empty;

	count = 6;
	while (count > 0)
	{
		line = get_next_line(fd, &is_empty);
		if (!line && is_empty == 0)
			return (write(2, "Error\nget_next_line fill_infos error\n", 37));
		if (ft_strchr("NSFWEC", line[0]))
		{
			if (gateway_textures(line, map, &count))
				return (free_infos(map), 1);
		}
		else if (line[0] != '\n')
			return (free_infos(map), free(line), \
						write(2, "Error\nIncorrect syntax\n", 23));
		free(line);
	}
	if (check_infos(map))
		return (1);
	return (0);
}

int	fill_map(int fd, t_map *map, char *av)
{
	int	i;

	if (fill_infos(fd, map))
		return (1);
	i = 1;
	if (init_map(map, fd, av))
		return (free_infos(map), 1);
	if (fill_tabmap(fd, map, &i))
		return (free_infos(map), 1);
	if (last_row(&(map->map[i]), map->col))
		return (ft_free_tab_int(map->map), 1);
	map->map[++i] = 0;
	close(fd);
	return (0);
}

void	pre_init(t_map *map)
{
	map->map = NULL;
	map->c_rgb = -1;
	map->f_rgb = -1;
	map->n_t = NULL;
	map->s_t = NULL;
	map->e_t = NULL;
	map->w_t = NULL;
	map->d_t = NULL;
	map->row = -1;
	map->col = -1;
	map->x_spawn = -1;
	map->y_spawn = -1;
	map->puff = 0;
	map->el_mordjene = 0;
	map->doors = 0;
}

int	resize_map(t_map *map)
{
	int	pre_empty_col;
	int	post_empty_col;
	int	**newmap;
	int	i;

	pre_empty_col = count_pre_col(map->map);
	post_empty_col = count_post_col(map->map, map->col + 2);
	map->col = map->col + 4 - post_empty_col - pre_empty_col;
	newmap = ft_calloc((map->row + 3), sizeof(int *));
	if (!newmap)
		return (ft_free_tab_int(map->map), \
					write(2, "Error\nMalloc map fail\n", 22));
	i = 0;
	while (i <= (map->row + 1))
	{
		if (resize_line(map->map[i], &newmap[i], pre_empty_col, map->col))
			return (ft_free_tab_int(map->map), ft_free_tab_int(newmap), \
						write(2, "Error\nMalloc map fail\n", 22));
		i++;
	}
	ft_free_tab_int(map->map);
	map->map = newmap;
	map->row += 2;
	return (0);
}

int	parsing(char *av, t_map *map)
{
	int		fd_map;

	pre_init(map);
	if (check_av(av, &fd_map))
		return (1);
	if (fill_map(fd_map, map, av))
		return (close_void(fd_map), 1);
	if (check_map(map))
		return (free_map(map), 1);
	if (resize_map(map))
		return (free_infos(map), 1);//TODO pourquoi free_infos et pas free_map
	set_pos_spawn(map);
	if (map->doors)
	{
		map->d_t = ft_strdup(DOOR_TEXTURE);
		if (!map->d_t)
		{
			write(2, "Error\nft_strdup failed\n", 23);
			free_map(map);
		}
	}
	return (0);
}
