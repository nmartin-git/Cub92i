/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:23:42 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/13 03:34:46 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "struct_utils.h"
# include "game.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <limits.h>
# define EMPTY_COLOR 0
# define MINIMAP_SIZE 10000
# define QUALITY 100
# define WALL 1
# define FLOOR 0
# define EMPTY 8
# define STEP 0.5f
# define ROTATION 0.1
# define PI 3.1415926535
# define FOV 60
# define RAY_NBR /*60*/ 1920
# define TAN_ERR 9999
# define HORIZONTAL 1
# define VERTICAL 2

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
void	go_left(t_data *data, int pixels);
void	go_right(t_data *data, int pixels);
void	go_up(t_data *data, int pixels);
void	go_down(t_data *data, int pixels);

/*---step.c---*/

void	left_step(t_data *data, __uint64_t step);
void	right_step(t_data *data, __uint64_t step);
void	forward_step(t_data *data, __uint64_t step);
void	backward_step(t_data *data, __uint64_t step);

/*---raycasting.c---*/
void	pixel_put(t_image *raycasting, t_pos pixel, int color);
void	small_angle(t_image *raycasting, t_pos pixel, int dx, int dy);
void	big_angle(t_image *raycasting, t_pos pixel, int dx, int dy);
void	put_raycasting(t_minimap *minimap, float fov, int ray_nbr, t_data *data);

/*---rays.c---*/
int		is_wall(t_minimap *minimap, t_data *data, t_pos *pos);
void	vertical_wall(t_minimap *minimap, t_data *data, t_pos *pos, float angle);
void	horizontal_wall(t_minimap *minimap, t_data *data, t_pos *pos, float angle);
void	set_nearest(t_minimap *minimap, t_pos *p1, t_pos *p2, float angle);
t_ray	*raycast(t_minimap *minimap, t_ray *ray, t_data *data, t_pos *result);

#endif