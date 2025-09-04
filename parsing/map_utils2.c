/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:47:47 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/03 18:46:07 by nmartin          ###   ########.fr       */
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
	else if (c == 'M')
		return (MORDJENE);
	else if (c == 'F')
		return (PUFF);
	return (-2);
}

/*
compte le nombre d'ennemis, de puffs et de el mordjene
*/

void	count_collectible(char c, t_map *map)
{
	if (c == MORDJENE)
		map->el_mordjene++;
	if (c == PUFF)
		map->puff++;
}
