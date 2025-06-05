/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:50:13 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/05 16:07:21 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

int	is_col_empty(int **map, int i)
{
	int	j;

	j = 0;
	while (map[j])
	{
		if (map[j][i] != 8)
			return (1);
		j++;
	}
	return (0);
}

int	count_pre_col(int **map)
{
	int	i;

	i = 0;
	while (is_col_empty(map, i) == 0)
		i++;
	return (i);
}

int	count_post_col(int **map, int size)
{
	int	i;

	i = 0;
	while (is_col_empty(map, --size) == 0)
		i++;
	return (i);
}

int	resize_line(int *map, int **newmap, int start, int size)
{
	int	i;

	i = 0;
	(*newmap) = ft_calloc(size + 1, sizeof(int));
	if (!(*newmap))
		return (1);
	while (i < size)
	{
		(*newmap)[i] = map[(start - 1) + i];
		i++;
	}
	(*newmap)[i] = 9;
	return (0);
}
