/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:23:42 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/23 18:05:34 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "struct_utils.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <limits.h>
# define EMPTY_COLOR 0
# define MINIMAP_SIZE 1400
# define WALL 1
# define FLOOR 0
# define EMPTY 8
# define STEP 3
# define ROTATION 0.1
# define PI 3.1415926535
# define FOV 60
# define RAY_NBR 60
# define TAN_ERR 9999

enum e_input
{
	W,
	A,
	S,
	D
};

/*---minimap.c---*/
void	set_minimap_color(t_minimap *minimap);
int		get_minimap_color(t_minimap *minimap, int content);
void	minimap_data(t_minimap *minimap, t_data *data);
void	pixel_put_square(t_minimap *minimap, t_pos pixel, int color);
void	minimap_create(t_minimap *minimap, t_data *data);

/*---cursor.c---*/
void	put_cursor_direction(t_minimap *minimap);
void	pixel_put_cursor(t_image *cursor, int color, int size, int radius);

/*---collision.c*/
void	go_left(t_data *data);
void	go_right(t_data *data);
void	go_up(t_data *data);
void	go_down(t_data *data);

/*---raycasting.c---*/
void	pixel_put(t_image *raycasting, t_pos pixel, int color);
void	small_angle(t_image *raycasting, t_pos pixel, int dx, int dy);
void	big_angle(t_image *raycasting, t_pos pixel, int dx, int dy);
void	put_raycasting(t_minimap *minimap, double fov, int ray_nbr, t_data *data);

/*---rays.c---*/
int		is_wall(t_minimap *minimap, t_data *data, t_pos *pos);
void	vertical_wall(t_minimap *minimap, t_data *data, t_pos *pos, double angle);
void	horizontal_wall(t_minimap *minimap, t_data *data, t_pos *pos, double angle);
void	set_nearest(t_minimap *minimap, t_pos *p1, t_pos *p2, double angle);
t_pos	*raycast(t_minimap *minimap, double angle, t_data *data, t_pos *result);

#endif