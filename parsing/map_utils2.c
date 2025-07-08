/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:47:47 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/08 16:03:12 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

/*
suite de ctoi
*/

int	ctoi2(char c)
{
	if (c == ' ' || c == '\n')
		return (8);
	else if (c == 'I')
		return (6);
	else if (c == 'A')
		return (7);
	else if (c == 'M')
		return (10);
	else if (c == 'F')
		return (11);
	else if (c == 'C')
		return (12);
	return (ft_putstr_fd("Error\nInvalid character\n", 2), -2);
}

/*
compte le nombre d'ennemis, de puffs et de el mordjene
*/

void	count_collectible(char c, t_map *map)
{
	if (c == 6)
		map->_92i++;
	if (c == 7)
		map->paqueta++;
	if (c == 10)
		map->el_mordjene++;
	if (c == 11)
		map->puff++;
	if (c == 12)
		map->chicha++;
}
