/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:26:13 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/07 22:19:30 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	mooveCursor(t_data *data, int input)
{
	if (input == A || input == D)
		isXWall(data, input);
	else
		isYWall(data, input);
	mlx_clear_window(data->display, data->window);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
	mlx_put_image_to_window(data->display, data->window, data->minimap->minimap->image, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	mlx_put_image_to_window(data->display, data->window, data->minimap->cursor->image, data->minimap->cursor_x, data->minimap->cursor_y);
}

int	key_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		cub_exit(0, "Window closed successfully", data);
	if (key == XK_w || key == XK_W)
		mooveCursor(data, W);
	if (key == XK_a || key == XK_A)
		mooveCursor(data, A);
	if (key == XK_s || key == XK_S)
		mooveCursor(data, S);
	if (key == XK_d || key == XK_D)
		mooveCursor(data, D);
	return (0);
}
