/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:35 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/08 16:03:04 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

/*
va remplir les informations utiles à la map
*/

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

/*
va remplir la structure map
*/

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

/*
initialise la structure map avant utilisation
*/

void	pre_init(t_map *map)
{
	map->map = NULL;
	map->c_rgb = -1;
	map->f_rgb = -1;
	map->n_t = NULL;
	map->s_t = NULL;
	map->e_t = NULL;
	map->w_t = NULL;
	map->row = -1;
	map->col = -1;
	map->x_spawn = -1;
	map->y_spawn = -1;
	map->_92i = 0;
	map->paqueta = 0;
	map->el_mordjene = 0;
	map->puff = 0;
	map->chicha = 0;
}

/*
va recréer une map plus propre pour effacer des colonnes et
les lignes vides en extrémité de la map parsée
*/

int	resize_map(t_map *map)
{
	t_resize	tmp;
	int			**newmap;

	tmp.pre_empty_col = count_pre_col(map->map);
	tmp.post_empty_col = count_post_col(map->map, map->col + 2);
	tmp.post_empty_row = count_post_row(map->map, map->row + 1);
	map->row = map->row - tmp.post_empty_row;
	map->col = map->col + 4 - tmp.post_empty_col - tmp.pre_empty_col;
	newmap = ft_calloc((map->row + 3), sizeof(int *));
	if (!newmap)
		return (ft_free_tab_int(map->map), \
					write(2, "Error\nMalloc map fail\n", 22));
	tmp.i = 0;
	while (tmp.i <= (map->row + 1))
	{
		if (resize_line(map->map[tmp.i], &newmap[tmp.i], tmp.pre_empty_col, \
				map->col))
			return (ft_free_tab_int(map->map), ft_free_tab_int(newmap), \
						write(2, "Error\nMalloc map fail\n", 22));
		tmp.i++;
	}
	ft_free_tab_int(map->map);
	map->map = newmap;
	map->row += 2;
	return (0);
}

/* 
va parser l'argument passé à la commande et remplir
une t_map avec toutes les informations utiles à l'exec
*/

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
		return (free_infos(map), 1);
	set_pos_spawn(map);
	return (0);
}

// int main(int ac, char **av)
// {
// 	t_map map;
// 	(void)ac;
// 	if (parsing(av[1], &map))
// 		return 1;
// 	for (size_t i = 0; map.map[i] != 0; i++)
// 	{
// 		for (size_t j = 0; map.map[i][j] != 9; j++)
// 			printf("%d", map.map[i][j]);
// 		printf("\n");
// 	}
// 	printf("%d, %d\n", map.x_spawn, map.y_spawn);
// 	printf("%d, %d\n", map.row, map.col);
// 	printf("%d\n", map._92i);
// 	printf("%d\n", map.paqueta);
// 	printf("%d\n", map.el_mordjene);
// 	printf("%d\n", map.puff);
// 	printf("%d\n", map.chicha);
// 	// printf("%s\n", map.n_t);
// 	// printf("%s\n", map.s_t);
// 	// printf("%s\n", map.e_t);
// 	// printf("%s\n", map.w_t);
// 	// printf("%d\n", map.f_rgb);
// 	// printf("%d\n", map.c_rgb);
// 	// printf("r %d, g %d, b %d\n", decode_r(map.f_rgb), decode_g(map.f_rgb),
// 	// 	decode_b(map.f_rgb));
// 	// printf("r %d, g %d, b %d\n", decode_r(map.c_rgb), decode_g(map.c_rgb),
// 	// 	decode_b(map.c_rgb));
// 	free_map(&map);
// 	return (0);
// }