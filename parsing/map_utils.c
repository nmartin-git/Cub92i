/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:43:53 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/04 12:50:02 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		if ((*col) < ft_strlen(line))
			(*col) = ft_strlen(line);
	}
	(*col)--;
	return (count - 1);
}

int	ctoi(char c, int *count)
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

int	encode_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
