/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:26:13 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/07 16:55:42 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	mooveCursor(t_data *data, int x, int y)
{
	data->minimap->cursor_x += x;
	data->minimap->cursor_y += y;
	mlx_clear_window(data->display, data->window);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
	mlx_put_image_to_window(data->display, data->window, data->minimap->minimap->image, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	mlx_put_image_to_window(data->display, data->window, data->minimap->cursor->image, data->minimap->cursor_x, data->minimap->cursor_y);
}

int	key_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		cub_exit(0, "Window closed successfully", data);
	if (key == XK_Right)
		mooveCursor(data, data->minimap->squareSize / 8, 0);
	if (key == XK_Left)
		mooveCursor(data, -(data->minimap->squareSize / 8), 0);
	if (key == XK_Up)
		mooveCursor(data, 0, -(data->minimap->squareSize / 8));
	if (key == XK_Down)
		mooveCursor(data, 0, data->minimap->squareSize / 8);
	return (0);
}
