/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:26:13 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/12 20:00:45 by nmartin          ###   ########.fr       */
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
	// clearImage(data->minimap->direction);
	clearImage(data->minimap->raycasting);
	// putCursorDirection(data->minimap);
	putRaycasting(data->minimap, FOV, RAY_NBR);
	mlx_clear_window(data->display, data->window);
	put_img_to_img(data->image, data->minimap->minimap, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	put_img_to_img(data->image, data->minimap->raycasting, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	put_img_to_img(data->image, data->minimap->direction, data->minimap->cursor_x - data->minimap->squareSize * 2/3, data->minimap->cursor_y - data->minimap->squareSize * 2/3);
	put_img_to_img(data->image, data->minimap->cursor, data->minimap->cursor_x, data->minimap->cursor_y);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
}

void	mooveCursor(t_data *data, int direction)
{
	data->minimap->p_angle += DIRECTION * direction;
	clearImage(data->minimap->direction);
	clearImage(data->minimap->raycasting);
	putCursorDirection(data->minimap);
	putRaycasting(data->minimap, FOV, RAY_NBR);
	mlx_clear_window(data->display, data->window);
	put_img_to_img(data->image, data->minimap->minimap, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	put_img_to_img(data->image, data->minimap->raycasting, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	put_img_to_img(data->image, data->minimap->direction, data->minimap->cursor_x - data->minimap->squareSize * 2/3, data->minimap->cursor_y - data->minimap->squareSize * 2/3);
	put_img_to_img(data->image, data->minimap->cursor, data->minimap->cursor_x, data->minimap->cursor_y);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
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
		mooveCursor(data, -1);
	if (key == XK_Right)
		mooveCursor(data, 1);
	return (0);
}
