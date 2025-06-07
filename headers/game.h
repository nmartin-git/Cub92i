/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:55:19 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/07 16:55:13 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "libft.h"
# include "parsing.h"
# include "minimap.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>

# define TAB_X 1920//1280
# define TAB_Y 1080//720

//---game.c---
int		close_window(t_data *data);
void	set_data(t_data *data, t_map *map);
void	game(t_data *data, t_map *map);
int		minimap(t_data *data);

//---game_utils.c---
void	cub_exit(int err, char *str, t_data *data);
void	free_data(t_data *data);

/*---key_handling.c---*/
void	mooveCursor(t_data *data, int x, int y);
int		key_handler(int key, t_data *data);

#endif