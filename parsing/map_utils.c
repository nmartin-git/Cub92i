/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:43:53 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/12 17:20:54 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

/*
avance dans le fichier jusqu'à arriver sur la map
*/

int	start_of_map(int fd, char **line)
{
	int	is_empty;

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

/*
compte la taille de la map et renvoie le nombre de lignes
*/

int	count_size(int fd, int *col)
{
	char	*line;
	int		count;
	int		is_empty;

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
		if ((*col) < (int)ft_strlen(line))
			(*col) = ft_strlen(line);
	}
	(*col)--;
	return (count - 1);
}

/*
char to int avec les spécificités de la map
*/

int	ctoi(char c, int *count)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c == 'N')
	{
		(*count)--;
		return (N_DIR);
	}
	else if (c == 'S')
	{
		(*count)--;
		return (S_DIR);
	}
	else if (c == 'E')
	{
		(*count)--;
		return (E_DIR);
	}
	else if (c == 'W')
	{
		(*count)--;
		return (W_DIR);
	}
	else if (c == ' ' || c == '\n')
		return (8);
	return (ft_putstr_fd("Error\nIncorect character\n", 2), -2);
}

/*
encode les couleur rgb en un seul int
*/

int	encode_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/*
sauvegarde la couleur du sol et du plafond dans la structure t_map
*/

void	fill_rgb(char **str, t_map *map, char c)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(str[0]);
	g = ft_atoi(str[1]);
	b = ft_atoi(str[2]);
	if (c == 'F')
	{
		if (r == 0 && g == 0 && b == 0)
			map->f_rgb = -10;
		if (r == 100 && g == 100 && b == 100)
			map->f_rgb = -11;
		if (r == 200 && g == 100 && b == 100)
			map->f_rgb = -12;
		else
			map->f_rgb = encode_rgb(r, g, b);
	}
	if (c == 'C')
		map->c_rgb = encode_rgb(r, g, b);
}
