/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:26:13 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/07 20:51:42 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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

void	update_2(t_data *data)
{
	if (data->mmap->cursor_x / data->sc_mmap->cursor_x > 63)
		data->sc_mmap->cursor_x = data->mmap->cursor_x / 63;
	if (data->mmap->cursor_x / data->sc_mmap->cursor_x < 62)
		data->sc_mmap->cursor_x = data->mmap->cursor_x / 62;
	if (data->mmap->cursor_y / data->sc_mmap->cursor_y > 63)
		data->sc_mmap->cursor_y = data->mmap->cursor_y / 63;
	if (data->mmap->cursor_y / data->sc_mmap->cursor_y < 62)
		data->sc_mmap->cursor_y = data->mmap->cursor_y / 62;
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
	update_2(data);
	return (0);
}
