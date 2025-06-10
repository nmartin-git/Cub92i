/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:26:13 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/10 20:12:56 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	clearImage(t_image *image)
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

void	moovePlayer(t_data *data, int input)
{
	if (input == A || input == D)
		isXWall(data, input);
	else
		isYWall(data, input);
	clearImage(data->minimap->direction);
	putCursorDirection(data->minimap);
	mlx_clear_window(data->display, data->window);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
	mlx_put_image_to_window(data->display, data->window, data->minimap->minimap->image, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	mlx_put_image_to_window(data->display, data->window, data->minimap->direction->image, data->minimap->cursor_x - data->minimap->squareSize * 2/3, data->minimap->cursor_y - data->minimap->squareSize * 2/3);
	mlx_put_image_to_window(data->display, data->window, data->minimap->cursor->image, data->minimap->cursor_x, data->minimap->cursor_y);
}

void	mooveCursor(t_data *data, int direction)
{
	data->minimap->p_angle += DIRECTION * direction;
	clearImage(data->minimap->direction);
	putCursorDirection(data->minimap);
	mlx_clear_window(data->display, data->window);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
	mlx_put_image_to_window(data->display, data->window, data->minimap->minimap->image, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	mlx_put_image_to_window(data->display, data->window, data->minimap->direction->image, data->minimap->cursor_x - data->minimap->squareSize * 2/3, data->minimap->cursor_y - data->minimap->squareSize * 2/3);
	mlx_put_image_to_window(data->display, data->window, data->minimap->cursor->image, data->minimap->cursor_x, data->minimap->cursor_y);
}

int	key_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		cub_exit(0, "Window closed successfully", data);
	if (key == XK_w || key == XK_W)
		moovePlayer(data, W);
	if (key == XK_a || key == XK_A)
		moovePlayer(data, A);
	if (key == XK_s || key == XK_S)
		moovePlayer(data, S);
	if (key == XK_d || key == XK_D)
		moovePlayer(data, D);
	if (key == XK_Left)
		mooveCursor(data, 1);
	if (key == XK_Right)
		mooveCursor(data, -1);
	return (0);
}
