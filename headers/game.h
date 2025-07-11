/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:55:19 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/11 22:35:46 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../minilibx-linux/mlx.h"
# include "background.h"
# include "crosshair.h"
# include "libft.h"
# include "minimap.h"
# include "parsing.h"
# include <X11/keysym.h>

# define TAB_X 1920 // 1280
# define TAB_Y 1080 // 720

//---game.c---
int		close_window(t_data *data);
void	set_data(t_data *data, t_map *map);
void	game(t_data *data, t_map *map);
int		minimap(t_data *data);

//---game_utils.c---
void	cub_exit(int err, char *str, t_data *data);
void	free_data(t_data *data);

/*---key_handling.c---*/
void	clear_image(t_image *image);
void	moove_player(t_data *data, int input);
void	moove_cursor(t_data *data, int direction);
int		key_handler(int key, t_data *data);
int		mouse_move(int x, int y, t_data *data);

#endif