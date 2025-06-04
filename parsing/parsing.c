/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:35 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/04 11:57:26 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parsing.h"
// #include "../headers/game.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int	encode_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	decode_r(int rgb)
{
	return ((rgb >> 16) & 255);
}

int	decode_g(int rgb)
{
	return ((rgb >> 8) & 255);
}

int	decode_b(int rgb)
{
	return (rgb & 255);
}

void ft_free_tab_int(int **tab)
{
    int i;

    i = 0;
    while (tab[i])
        free(tab[i++]);
    free(tab);
    tab = NULL;
}

void close_void(int fd)
{
    close(fd);
}

void free_infos(t_map *map)
{
    if (map->n_t)
        free(map->n_t);
    if (map->s_t)
        free(map->s_t);
    if (map->e_t)
        free(map->e_t);
    if (map->w_t)
        free(map->w_t);
}

void free_map(t_map *map)
{
    free_infos(map);
    ft_free_tab_int(map->map);    
}

int	fill_t(char *line, t_map *map, char c1, char c2)
{
    char **texture;

    if (line[1] && line[1] == ' ')
        line = &line[2];
    else if (line[1] && line[2] && line[1] == c2 && line[2] == ' ')
        line = &line[3];
    else
        return (write(2, "Error\nIncorrect texture syntax\n", 31));
    texture = NULL;
    if (c1 == 'N')
        texture = &map->n_t;
    else if (c1 == 'S')
        texture = &map->s_t;
    else if (c1 == 'E')
        texture = &map->e_t;
    else if (c1 == 'W')
        texture = &map->w_t;
    else
        return (write(2, "Error\nUnknown texture code\n", 29));
    *texture = ft_substr(line, 0, (ft_strlen(line) - 1));
    if (!*texture)
        return (write(2, "Error\nft_strdup fail\n", 21));
    return (0);
}

int fill_colors(char *line, t_map *map, char c)
{
    int r;
    int g;
    int b;
    char **str;

    if (line[1] && line[1] != ' ' && ft_strlen(line) > 14)
        return (write(2, "Error\nIncorrect texture syntax\n", 31));
    line = &line[2];
    str = ft_split(line, ',');
    if (!str)
        return (write(2, "Error\nSplit fail\n", 17));
    r = ft_atoi(str[0]);
    g = ft_atoi(str[1]);
    b = ft_atoi(str[2]);
    if (c == 'F')
        map->f_rgb = encode_rgb(r, g, b);
    if (c == 'C')
        map->c_rgb = encode_rgb(r, g, b);
    ft_free_tab(str);
    return (0);
}

int	fill_textures(char *line, t_map *map, int *count)
{
	if (line[0] == 'N' && !map->n_t)
    {
        (*count)--;
		if (fill_t(line, map, 'N', 'O'))
			return (1);
    }
    if (line[0] == 'S' && !map->s_t)
	{
        (*count)--;
    	if (fill_t(line, map, 'S', 'O'))
			return (1);
    }
    if (line[0] == 'F' && map->f_rgb == -1)
    {
        (*count)--;
        if (fill_colors(line, map, 'F'))
            return (1);
    }
    if (line[0] == 'W' && !map->w_t)
	{
        (*count)--;
        if (fill_t(line, map, 'W', 'E'))
			return (1);
    }
    return (0);
}

int fill_EC(char *line, t_map *map, int *count)
{
    if (line[0] == 'E' && !map->e_t)
	{
        (*count)--;
        if (fill_t(line, map, 'E', 'A'))
			return (1);
    }
    if (line[0] == 'C' && map->c_rgb == -1)
    {
        (*count)--;
        if (fill_colors(line, map, 'C'))
            return (1);
    }
    return (0);
}

int gateway_textures(char *line, t_map *map, int *count)
{
    if (ft_strchr("NSFW", line[0]))
    {
		if (fill_textures(line, map, count))
            return (free(line), 1);
    }
    else if (ft_strchr("EC", line[0]))
    {
        if (fill_EC(line, map, count))
            return (free(line), 1);
    }
    return (0);
}

int check_infos(t_map *map)
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

int	fill_infos(int fd, t_map *map)
{
	char	*line;
    int     count;
    int     is_empty;

    count = 6;
	while (count > 0)
	{
        line = get_next_line(fd, &is_empty);
        if (!line && is_empty == 0)
            return (write(2, "Error\nget_next_line fill_infos error\n", 37));
		if (ft_strchr("NSFWEC", line[0]))
        {
            if (gateway_textures(line, map, &count))
                return (1);
        }
        else if (line[0] != '\n')
            return (free(line), write(2, "Error\nIncorrect syntax\n", 23));
        free(line);
	}
    if (check_infos(map))
        return (1);
    return (0);
}

int start_of_map(int fd, char **line)
{
    int is_empty;

    (*line) = get_next_line(fd, &is_empty);
    if (!(*line) && !is_empty)
        return (write(2, "Error\nget_next_line start_of_map error\n", 39));
    while ((*line) && ((*line)[0] != '1' && (*line)[0] != ' '))
    {
        free(*line);
        (*line) = get_next_line(fd, &is_empty);
        if (!(*line) && !is_empty)
            return (write(2, "Error\nget_next_line start_of_map error\n", 39));
    }
    return (0);
}

int count_size(int fd, int *col)
{
    char *line;
    int count;
    int is_empty;

    count = 1;
    if (start_of_map(fd, &line))
        return (-1);
    if (!line)
        return (ft_putstr_fd("Error\nMap is empty\n", 2), -1);
    (*col) = ft_strlen(line);
    while (line)
    {
        free(line);
        line = get_next_line(fd, &is_empty);
        if (!line && !is_empty)
            return (write(2, "Error\nget_next_line count_row error\n", 36));
        count++;
        if ((*col) < ft_strlen(line))
            (*col) = ft_strlen(line);
    }
    (*col)--;
    return (count - 1);
}

int ctoi(char c, int *count)
{
    if (c >= '0' && c <= '9')
        return (c - '0');
    else if (c == 'N')
    {
        (*count)--;
        return (2);
    }
    else if (c == 'S')
    {
        (*count)--;
        return (3);
    }
    else if (c == 'E')
    {
        (*count)--;
        return (4);
    }
    else if (c == 'W')
    {
        (*count)--;
        return (5);
    }
    else if (c == ' ' || c == '\n')
        return (8);
    return (ft_putstr_fd("Error\nIncorect character\n", 2), -2);
}

int fill_row(int **row, char *line, int col, int *count_spawn)
{
    int i;
    int len;

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
                return (free(line), write(2, "Error\nMap contains duplicates\n", 30));
        }
        else
            (*row)[i] = 8;
        i++;
    }
    (*row)[i] = 9;
    return (free(line), 0);
}

int init_map(t_map *map, int fd, char *av)
{
    int i;

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
        return (free(map->map), write(2, "Error\nOpen fill_tabmap fail\n", 28));
    map->map[0] = ft_calloc((map->col + 3), sizeof(int));
    if (!(map->map[0]))
        return (ft_free_tab_int(map->map), write(2, "Error\nMalloc map fail\n", 22));
    while (++i < (map->col + 2))
        map->map[0][i] = 8;
    map->map[0][i] = 9;
    return (0);
}

int last_row(int **row, int col)
{
    int i;

    i = -1;
    (*row) = ft_calloc((col + 3), sizeof(int));
    if (!(*row))
        return (write(2, "Error\nMalloc map fail\n", 22));
    while (++i < (col + 2))
        (*row)[i] = 8;
    (*row)[i] = 9;
    return (0);
}

int fill_tabmap(int fd, t_map *map, char *av, int *i)
{
    char *line;
    int is_empty;
    int count_spawn;

    count_spawn = 1;
    if (init_map(map, fd, av))
        return (1);
    if (start_of_map(fd, &line))
        return (1);
    while ((*i) < (map->row + 1))
    {
        map->map[(*i)] = ft_calloc((map->col + 3), sizeof(int));
        if (!(map->map[(*i)]))
            return (ft_free_tab_int(map->map), free(line), write(2, "Error\nMalloc map fail\n", 22));
        if (fill_row(&(map->map[(*i)]), line, map->col, &count_spawn))
            return (ft_free_tab_int(map->map), 1);
        line = get_next_line(fd, &is_empty);
        if (!line && !is_empty)
            return (ft_free_tab_int(map->map), write(2, "Error\nget_next_line fill_tabmap error\n", 38));
        (*i)++;
    }
    if (count_spawn)
        return (ft_free_tab_int(map->map), write(2, "Error\nMissing spawn point\n", 26));
    return (0);
}       

int	fill_map(int fd, t_map *map, char *av)
{
    int i;

	if (fill_infos(fd, map))
		return (1);
    i = 1;
    if (fill_tabmap(fd, map, av, &i))
        return (free_infos(map), 1);
    if (last_row(&(map->map[i]), map->col))
        return (ft_free_tab_int(map->map), 1);
    map->map[++i] = 0;
    close(fd);
    return (0);
}

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

void pre_init(t_map *map)
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
}

int check_neighbors(t_map *map, int x, int y)
{
    if (y - 1 >= 0 && x - 1 >= 0 && map->map[y - 1][x - 1] != 8 && map->map[y - 1][x - 1] != 1)
        return (write(2, "Error\nInvalid map\n", 18));
    if (y + 1 <= map->row && x - 1 >= 0 && map->map[y + 1][x - 1] != 8 && map->map[y + 1][x - 1] != 1)
        return (write(2, "Error\nInvalid map\n", 18));
    if (y - 1 >= 0 && x + 1 < map->col && map->map[y - 1][x + 1] != 8 && map->map[y - 1][x + 1] != 1)
        return (write(2, "Error\nInvalid map\n", 18));
    if (y + 1 <= map->row && x + 1 < map->col && map->map[y + 1][x + 1] != 8 && map->map[y + 1][x + 1] != 1)
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

int check_map(t_map *map)
{
    int x;
    int y;

    y = 0;
    while (map->map[y])
    {
        x = 0;
        while (map->map[y][x] != 9)
        {
            if (map->map[y][x] == 8)
            {
                if (map->map[y][x] == 8)
                    if (check_neighbors(map, x, y))
                        return (1);
            }
            x++;
        }
        y++;
    }    
    return (0);
}

int	parsing(char *av)
{
	int	fd_map;
    t_map map;
    
    pre_init(&map);
	if (check_av(av, &fd_map))
		return (1);
	if (fill_map(fd_map, &map, av))
		return (close_void(fd_map), 1);
    if (check_map(&map))
        return (free_map(&map), 1);
    for (size_t i = 0; map.map[i] != 0; i++)
    {
        for (size_t j = 0; map.map[i][j] != 9; j++)
            printf("%d", map.map[i][j]);
        printf("\n");
    }
    printf("%d, %d\n", map.row, map.col);
    printf("%s\n", map.n_t);
    printf("%s\n", map.s_t);
    printf("%s\n", map.e_t);
    printf("%s\n", map.w_t);
    printf("%d\n", map.f_rgb);
    printf("%d\n", map.c_rgb);
    printf("r %d, g %d, b %d\n", decode_r(map.f_rgb), decode_g(map.f_rgb), decode_b(map.f_rgb));
    printf("r %d, g %d, b %d\n", decode_r(map.c_rgb), decode_g(map.c_rgb), decode_b(map.c_rgb));
    free_map(&map);
    return (0);
}

int	main(int ac, char **av)
{
	parsing(av[1]);
}
