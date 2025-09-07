/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:43:53 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/07 20:07:30 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

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

int	ctoi(char c, int *count)
{
	if (c >= '0' && c <= '1')
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
	return (ctoi2(c));
}

int	encode_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	fill_rgb(char **str, t_map *map, char c)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(str[0]);
	g = ft_atoi(str[1]);
	b = ft_atoi(str[2]);
	if (c == 'C')
	{
		if (r == 0 && g == 0 && b == 0)
			map->c_rgb = -10;
		else if (r == 100 && g == 100 && b == 100)
			map->c_rgb = -11;
		else if (r == 200 && g == 200 && b == 200)
			map->c_rgb = -12;
		else
			map->c_rgb = encode_rgb(r, g, b);
	}
	if (c == 'F')
		map->f_rgb = encode_rgb(r, g, b);
}
