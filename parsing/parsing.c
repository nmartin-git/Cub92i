/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:35 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/03 14:15:24 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parsing.h"
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

int	fill_t(char *line, t_map *map, char c1, char c2)
{
    char **texture;

    if (line[1] && line[1] == ' ')
        line = &line[2];
    else if (line[1] && line[2] && line[1] == c1 && line[2] == ' ')
        line = &line[3];
    else
        return (write(2, "Error\nIncorrect texture syntax\n", 31));
    texture = NULL;
    if (c1 == 'N')
        texture = &map->N_t;
    else if (c1 == 'S')
        texture = &map->S_t;
    else if (c1 == 'E')
        texture = &map->E_t;
    else if (c1 == 'W')
        texture = &map->W_t;
    else
        return (write(2, "Error\nUnknown texture code\n", 29));
    *texture = ft_strdup(line);
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
        map->F_rgb = encode_rgb(r, g, b);
    if (c == 'C')
        map->C_rgb = encode_rgb(r, g, b);
    return (0);
}

int	fill_textures(char *line, t_map *map, int *count)
{
	if (line[0] == 'N' && !map->N_t)
    {
        *count--;
		if (fill_t(line, map, 'N', 'O'))
			return (1);
    }
    if (line[0] == 'S' && !map->S_t)
	{
        *count--;
    	if (fill_t(line, map, 'S', 'O'))
			return (1);
    }
    if (line[0] == 'F' && !map->F_rgb)
    {
        *count--;
        if (fill_colors(line, map, 'F'))
            return (1);
    }
    if (line[0] == 'W' && !map->W_t)
	{
        *count--;
        if (fill_t(line, map, 'W', 'E'))
			return (1);
    }
    return (0);
}

int fill_FC(char *line, t_map *map, int *count)
{
    if (line[0] == 'E' && !map->E_t)
	{
        *count--;
        if (fill_t(line, map, 'E', 'A'))
			return (1);
    }
    if (line[0] == 'C' && !map->C_rgb)
    {
        *count--;
        if (fill_colors(line, map, 'C'))
            return (1);
    }
    return (0);
}

int check_infos(t_map *map)
{
    if (!map->N_t)
        return (write(2, "Error\nMissing information for north\n", 36));
    if (!map->S_t)
        return (write(2, "Error\nMissing information for south\n", 36));
    if (!map->E_t)
        return (write(2, "Error\nMissing information for east\n", 35));
    if (!map->W_t)
        return (write(2, "Error\nMissing information for weast\n", 36));
    if (!map->F_rgb)
        return (write(2, "Error\nMissing information for floor\n", 40));
    if (!map->C_rgb)
        return (write(2, "Error\nMissing information for ceiling\n", 38));
    return (0);
}

int	fill_infos(int fd, t_map *map)
{
	char	*line;
    int count;

    count = 6;
	while (count > 0)
	{
        line = get_next_line(fd);
        if (!line)
        {
            /* verifier si error */
        }
		if (ft_strchr("NSFW", line[0]))
			if (fill_textures(line, map, &count))
                return (free(line), 1);
        if (ft_strchr("EC", line[0]))
            if (fill_FC(line, map, &count))
                return (free(line), 1);
        if (line[0] != '\n')
            return (free(line), write(2, "Error\nIncorrect syntaxe\n", 24));
        free(line);
	}
    if (check_infos(map))
        return (1);
    return (0);
}

int	fill_map(int fd, t_map *map)
{
	if (fill_infos(fd, map))
		return (1);
    
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

int	parsing(char *av, t_data *data)
{
	int	fd_map;

	if (check_av(av, &fd_map))
		return (1);
	if (fill_map(fd_map, ))
		return (1);
}

int	main(int ac, char **av)
{
	(void)ac;
}
