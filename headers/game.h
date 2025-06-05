/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:55:19 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/05 14:36:50 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "libft.h"
# include "parsing.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>

# define TAB_X 1920//1280
# define TAB_Y 1080//720

typedef struct s_data
{
	void	*display;
	void	*window;
	void	*image;
	char	*adress;
	t_map	*map;
	int		bpp;
	int		l_len;
}	t_data;

//---game.c---
int		close_window(t_data *data);
int		key_handler(int key, t_data *data);
void	set_data(t_data *data, t_map *map);
void	game(t_data *data, t_map *map);

//---game_utils.c---
void	cub_exit(int err, char *str, t_data *data);
void	free_data(t_data *data);
void	free_map(int **map);

#endif