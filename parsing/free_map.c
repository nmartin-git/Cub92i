/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:37:25 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/08 16:35:33 by nmartin          ###   ########.fr       */
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
	if (map->d_t)
		free(map->d_t);
}

void	free_map(t_map *map)
{
	free_infos(map);
	ft_free_tab_int(map->map);
}
