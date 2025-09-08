/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:52:59 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/08 15:00:34 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	check_items(t_data *data, t_minimap *minimap)
{
	t_pos	pixel;

	pixel.x = (minimap->cursor_x + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) \
				/ minimap->pxl_size;
	pixel.y = (minimap->cursor_y + minimap->pxl_size / 3 - MINIMAP_SIZE / 15) \
				/ minimap->pxl_size;
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
			cub_exit(0, "Bien joue, toutes les puffs de Paquetta ont ete recuperees", data);
	}
	else
		return ;
	pixel_put_square(data->sc_mmap, pixel, data->mmap->f_color);
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
		while (x < image->tab_x)
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
	check_items(data, data->mmap);
}

void	move_cursor(t_data *data, int direction)
{
	data->mmap->p_angle += ROTATION / 3 * direction;
	if (data->mmap->p_angle > 2 * PI)
		data->mmap->p_angle = 0;
	if (data->mmap->p_angle < 0)
		data->mmap->p_angle = 2 * PI;
}

int	mouse_move(int x, int y, t_data *data)
{
	static int	last_x = TAB_X / 2;
	int			dx;

	(void)y;
	if (x == TAB_X / 2)
		return (0);
	dx = x - last_x;
	data->mmap->p_angle += dx * ROTATION * 0.005;
	if (data->mmap->p_angle > 2 * PI)
		data->mmap->p_angle = 0;
	if (data->mmap->p_angle < 0)
		data->mmap->p_angle = 2 * PI;
	mlx_mouse_move(data->display, data->window, TAB_X / 2, TAB_Y / 2);
	return (0);
}
