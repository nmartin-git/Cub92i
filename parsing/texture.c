/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:40:24 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/05 14:54:17 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

int	fill_t(char *line, t_map *map, char c1, char c2)
{
	char	**texture;

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

int	fill_colors(char *line, t_map *map, char c)
{
	int		r;
	int		g;
	int		b;
	char	**str;

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

int	fill_ec(char *line, t_map *map, int *count)
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

int	gateway_textures(char *line, t_map *map, int *count)
{
	if (ft_strchr("NSFW", line[0]))
	{
		if (fill_textures(line, map, count))
			return (free(line), 1);
	}
	else if (ft_strchr("EC", line[0]))
	{
		if (fill_ec(line, map, count))
			return (free(line), 1);
	}
	return (0);
}
