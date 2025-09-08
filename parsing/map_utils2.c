/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:47:47 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/08 15:22:39 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

int	ctoi2(char c)
{
	if (c == ' ' || c == '\n')
		return (8);
	else if (c == 'M')
		return (MORDJENE);
	else if (c == 'F')
		return (PUFF);
	else if (c == 'D')
		return (C_DOOR);
	return (-2);
}

void	count_collectible(char c, t_map *map)
{
	if (c == MORDJENE)
		map->el_mordjene++;
	if (c == PUFF)
		map->puff++;
	if (c == C_DOOR)
		map->doors++;
}

int	check_doors(t_map *map, int x, int y)
{
	if ((y - 1 >= 0 && map->map[y - 1][x] != 1 && \
		y + 1 <= map->row && map->map[y + 1][x] != 1) && \
		(x - 1 >= 0 && map->map[y][x - 1] != 1 && \
		x + 1 <= map->row && map->map[y][x + 1] != 1))
	{
		return (1);
	}
	return (0);
}
