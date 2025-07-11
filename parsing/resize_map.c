/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:50:13 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/25 18:32:21 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

/*
verifie si une colonne est un espace vide
*/

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

/*
compte le nombre de lignes vides en fin de fichiers
*/

int	count_post_row(int **map, int size)
{
	int	i;
	int	j;

	i = 0;
	while (size--)
	{
		j = 0;
		while (map[size][j] != 9)
		{
			if (map[size][j] != 8)
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
/*
compte le nombre de colonnes vides à gauche de la map
*/

int	count_pre_col(int **map)
{
	int	i;

	i = 0;
	while (is_col_empty(map, i) == 0)
		i++;
	return (i);
}

/*
compte le nombre de colonnes vides à droite de la map
*/

int	count_post_col(int **map, int size)
{
	int	i;

	i = 0;
	while (is_col_empty(map, --size) == 0)
		i++;
	return (i);
}

/*
va copier les lignes de la map parsé en supprimant les espaces
vides à gauche et à droite
*/

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
