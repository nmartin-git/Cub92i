/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:37:25 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/07 20:07:05 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

void	ft_free_tab_int(int **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

void	close_void(int fd)
{
	close(fd);
}

void	free_infos(t_map *map)
{
	if (map->n_t)
		free(map->n_t);
	if (map->s_t)
		free(map->s_t);
	if (map->e_t)
		free(map->e_t);
	if (map->w_t)
		free(map->w_t);
}

void	free_map(t_map *map)
{
	free_infos(map);
	ft_free_tab_int(map->map);
}
