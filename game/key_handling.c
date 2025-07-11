/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:26:13 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/11 23:00:32 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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

void	moove_player(t_data *data, int input)
{
	if (input == A)
		left_step(data);
	else if (input == D)
		right_step(data);
	else if (input == W)
		forward_step(data);
	else
		backward_step(data);
}

void	moove_cursor(t_data *data, int direction)
{
	data->minimap->p_angle += ROTATION * direction;
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

int	key_handler(int key, t_data *data)
{
	// mettre flag azerty / qwerty modifiable
	if (key == XK_Escape)
		cub_exit(0, "Window closed successfully", data);
	if (key == XK_w || key == XK_W || key == XK_z || key == XK_Z)
		moove_player(data, W);
	if (key == XK_a || key == XK_A)
		moove_player(data, A);
	if (key == XK_s || key == XK_S || key == XK_q || key == XK_Q)
		moove_player(data, S);
	if (key == XK_d || key == XK_D)
		moove_player(data, D);
	if (key == XK_Left)
		moove_cursor(data, -1);
	if (key == XK_Right)
		moove_cursor(data, 1);
	return (0);
}
