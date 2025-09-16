/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:23:42 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/16 16:31:45 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "../minilibx-linux/mlx.h"
# include "game.h"
# include "struct_utils.h"
# include <X11/keysym.h>
# include <limits.h>
# include <math.h>

# define EMPTY_COLOR 0
# define MINIMAP_SIZE 23100
# define SCREEN_MINIMAP_SIZE 400
# define QUALITY 100

# define WALL 1
# define FLOOR 0
# define EMPTY 8

# define STEP 100
# define ROTATION 0.15
# define PI 3.14159265358979323846
# define FOV 60
# define RAY_NBR 1920
# define TAN_ERR 9999
# define HORIZONTAL 1
# define VERTICAL 2

# define HEAL 20

# define MORDJENE_COLOR 0xE6D295
# define MORDJENE_BG_COLOR 0xCDB577
# define PUFF_COLOR 0xFF69B4

typedef struct s_image		t_image;
typedef struct s_minimap	t_minimap;
typedef struct s_pos		t_pos;
typedef struct s_ray		t_ray;

typedef struct s_tmp2
{
	int						b;
	int						l;
	int						x;
	int						i;
	int						y;
}							t_tmp2;

typedef struct s_tmp3
{
	t_pos					id;
	t_pos					c;
	t_pos					dst;
	int						draw;
}							t_tmp3;

typedef struct s_wall
{
	t_pos					pixel;
	float					hauteur;
	int						j;
	int						start;
	int						tex_y;
	int						tex_x;
	int						invert;
	int						dx;
	int						dy;
	int						draw_w;
	int						draw_h;
}							t_wall;

enum						e_input
{
	W,
	A,
	S,
	D
};

/*---minimap.c---*/
void						set_minimap_color(t_minimap *minimap);
int							get_minimap_color(t_minimap *minimap, int content);
void						minimap_data(t_minimap *minimap, t_data *data,
								int size);
void						minimap_create(t_minimap *minimap, t_data *data);

/*---minimap_utils.c---*/
void						pixel_put_square(t_minimap *minimap, t_pos pixel,
								int color);
int							load_image(t_minimap *minimap, t_data *data);
void						pixel_put(t_image *raycasting, t_pos pixel,
								int color);
int							get_pixel_color(t_image *texture, int x, int y);
void						set_order_texture(t_image *texture, t_ray *ray,
								t_wall *tmp);

/*---cursor.c---*/
void						put_cursor_direction(t_minimap *minimap,
								float p_angle);
void						pixel_put_cursor(t_image *cursor, int color,
								int size, int radius);

/*---collision_screen.c---*/

void						go_left_screen(t_data *data, float pixels);
void						go_right_screen(t_data *data, float pixels);
void						go_up_screen(t_data *data, float pixels);
void						go_down_screen(t_data *data, float pixels);

/*---collision.c*/
void						go_left(t_data *data, int pixels);
void						go_right(t_data *data, int pixels);
void						go_up(t_data *data, int pixels);
void						go_down(t_data *data, int pixels);

/*---step.c---*/

void						left_step(t_data *data, __uint64_t step);
void						right_step(t_data *data, __uint64_t step);
void						forward_step(t_data *data, __uint64_t step);
void						backward_step(t_data *data, __uint64_t step);
void						diag_step(t_data *data, __uint64_t step, int state);

/*---raycasting.c---*/
void						small_angle(t_image *raycasting, t_pos pixel,
								int dx, int dy);
void						big_angle(t_image *raycasting, t_pos pixel, int dx,
								int dy);
void						put_raycasting(t_minimap *minimap, float fov,
								int ray_nbr, t_data *data);

/*---rays.c---*/
void						tan_err(t_pos *pos);
int							vertical_wall(t_minimap *minimap, t_data *d,
								t_pos *pos, double angle);
int							horizontal_wall(t_minimap *minimap, t_data *data,
								t_pos *pos, double angle);
void						raycast(t_minimap *minimap, t_ray *ray,
								t_data *data, t_pos *result);

/*---rays_norm.c---*/
double						normalize_angle(double angle);
void						tan_err(t_pos *pos);
								
/*---items.c---*/
void						put_pxl(t_image *image, int x, int y,
								unsigned int color);
void						put_mordjene(t_minimap *minimap, t_pos pos,
								int radius, int inner_radius);
void						put_puff(t_minimap *minimap, t_pos pos, int width,
								int height);

/*---sprites.c---*/
int							small_cast(t_data *d, t_pos pxl, int dx, int dy);
int							big_cast(t_data *d, t_pos pxl, int dx, int dy);
void						item_raycast(t_data *d, t_pos pos, int item);

/*---display_item.c---*/
void						set_item_rayscast(t_data *data);
void						item_on_map(t_data *data, int item, float pos,
								double qlqchose);

#endif