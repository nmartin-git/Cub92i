/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:55:19 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/03 18:52:34 by nmartin          ###   ########.fr       */
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
# define HEALTH 100
# define HEALTH_COLOR 123456
# define HEALTH_BG_COLOR 12345678

//---game.c---
int		close_window(t_data *data);
void	set_data(t_data *data, t_map *map);
void	pv_bar(t_data *data);
void	game(t_data *data, t_map *map);
int		minimap(t_data *data);

//---game_utils.c---
void	cub_exit(int err, char *str, t_data *data);
void	free_data(t_data *data);

/*---key_handling.c---*/
void	clear_image(t_image *image);
void	move_player(t_data *data, int input, __uint64_t delta_time);
void	move_cursor(t_data *data, int direction);
int		mouse_move(int x, int y, t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		update(t_data *data, __uint64_t delta_time);

#endif