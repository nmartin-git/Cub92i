/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:26:13 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/04 16:36:22 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	check_items(t_data *data, t_minimap *minimap)
{
	t_pos	pixel;
	
	pixel.x = (minimap->cursor_x + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) / minimap->pxl_size;
	pixel.y = (minimap->cursor_y + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) / minimap->pxl_size;
	if (data->map->map[pixel.y][pixel.x] == MORDJENE && data->health > 0)
	{
		data->health += HEAL;
		if (data->health > 100)
			data->health = 100;
		data->map->map[pixel.y][pixel.x] = FLOOR;
		clear_image(data->pv);
		pv_bar(data);
	}
	else if (data->map->map[pixel.y][pixel.x] == PUFF)
	{
		data->puff++;
		data->map->map[pixel.y][pixel.x] = FLOOR;
		if (data->puff >= data->map->puff)
		{
			free_data(data);
			exit (EXIT_SUCCESS);
		}
	}
	else
		return ;
	pixel_put_square(data->minimap, pixel, data->minimap->f_color);
}

void	clear_image(t_image *image)
{
	int		x;
	int		y;
	char	*pxl;

	y = 0;
	while (y < image->tab_y)
	{
		x = 0;
		while(x < image->tab_x)
		{
			pxl = image->adress + (y * image->l_len + x * (image->bpp / 8));
			*(unsigned int *)pxl = EMPTY_COLOR;
			x++;
		}
		y++;
	}
}

void	move_player(t_data *data, int input, __uint64_t delta_time)
{
	if (input == A)
		left_step(data, STEP * delta_time);
	else if (input == D)
		right_step(data, STEP * delta_time);
	else if (input == W)
		forward_step(data, STEP * delta_time);
	else if (input == S)
		backward_step(data, STEP * delta_time);
	else if (input == 4)
		diag_step(data, STEP * delta_time, 4);
	else if (input == 5)
		diag_step(data, STEP * delta_time, 5);
	else if (input == 6)
		diag_step(data, STEP * delta_time, 6);
	else if (input == 7)
		diag_step(data, STEP * delta_time, 7);
	check_items(data, data->minimap);
}

void	move_cursor(t_data *data, int direction)
{
	data->minimap->p_angle += ROTATION / 3 * direction;
	if (data->minimap->p_angle > 2 * PI)
		data->minimap->p_angle = 0;
	if (data->minimap->p_angle < 0)
		data->minimap->p_angle = 2 * PI;
}

int	mouse_move(int x, int y, t_data *data)
{
	static int	last_x = TAB_X / 2;
	int			dx;

	(void)y;
	if (x == TAB_X / 2)
		return (0);
	dx = x - last_x;
	data->minimap->p_angle += dx * ROTATION * 0.005;
	if (data->minimap->p_angle > 2 * PI)
		data->minimap->p_angle = 0;
	if (data->minimap->p_angle < 0)
		data->minimap->p_angle = 2 * PI;
	mlx_mouse_move(data->display, data->window, TAB_X / 2, TAB_Y / 2);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape && data->keys[0] == 0)
		data->keys[0] = 1;
	if ((keycode == XK_w || keycode == XK_W || keycode == XK_z || \
			keycode == XK_Z) && data->keys[1] == 0)
		data->keys[1] = 1;
	if ((keycode == XK_a || keycode == XK_A) && data->keys[2] == 0)
		data->keys[2] = 1;
	if ((keycode == XK_s || keycode == XK_S || keycode == XK_q || \
			keycode == XK_Q) && data->keys[3] == 0)
		data->keys[3] = 1;
	if ((keycode == XK_d || keycode == XK_D) && data->keys[4] == 0)
		data->keys[4] = 1;
	if (keycode == XK_Left && data->keys[5] == 0)
		data->keys[5] = 1;
	if (keycode == XK_Right && data->keys[6] == 0)
		data->keys[6] = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == XK_Escape && data->keys[0] == 1)
		data->keys[0] = 0;
	if ((keycode == XK_w || keycode == XK_W || keycode == XK_z || \
			keycode == XK_Z) && data->keys[1] == 1)
		data->keys[1] = 0;
	if ((keycode == XK_a || keycode == XK_A) && data->keys[2] == 1)
		data->keys[2] = 0;
	if ((keycode == XK_s || keycode == XK_S || keycode == XK_q || \
			keycode == XK_Q) && data->keys[3] == 1)
		data->keys[3] = 0;
	if ((keycode == XK_d || keycode == XK_D) && data->keys[4] == 1)
		data->keys[4] = 0;
	if (keycode == XK_Left && data->keys[5] == 1)
		data->keys[5] = 0;
	if (keycode == XK_Right && data->keys[6] == 1)
		data->keys[6] = 0;
	return (0);
}

int	update(t_data *data, __uint64_t delta_time)
{
	if (data->keys[0] == 1)
		cub_exit(0, "Window closed successfully", data);
	if (data->keys[1] == 1 && data->keys[2] == 1)
		move_player(data, 4, delta_time);
	else if (data->keys[1] == 1 && data->keys[4] == 1)
		move_player(data, 5, delta_time);
	else if (data->keys[3] == 1 && data->keys[2] == 1)
		move_player(data, 6, delta_time);
	else if (data->keys[3] == 1 && data->keys[4] == 1)
		move_player(data, 7, delta_time);
	else if (data->keys[1] == 1)
		move_player(data, W, delta_time);
	else if (data->keys[2] == 1)
		move_player(data, A, delta_time);
	else if (data->keys[3] == 1)
		move_player(data, S, delta_time);
	else if (data->keys[4] == 1)
		move_player(data, D, delta_time);
	if (data->keys[5] == 1)
		move_cursor(data, -1);
	if (data->keys[6] == 1)
		move_cursor(data, 1);
	return (0);
}
