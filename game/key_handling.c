/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:26:13 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/20 15:37:33 by nmartin          ###   ########.fr       */
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
		while(x < image->tab_x)
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
		go_left(data);
	else if(input == D)
		go_right(data);
	else if (input == W)
		go_up(data);
	else
		go_down(data);
	clear_image(data->minimap->direction);
	clear_image(data->minimap->raycasting);
	put_cursor_direction(data->minimap);
	put_raycasting(data->minimap, FOV, RAY_NBR, data);
	mlx_clear_window(data->display, data->window);
	put_img_to_img(data->image, data->minimap->minimap, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	put_img_to_img(data->image, data->minimap->raycasting, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	put_img_to_img(data->image, data->minimap->direction, data->minimap->cursor_x - data->minimap->pxl_size * 2/3, data->minimap->cursor_y - data->minimap->pxl_size * 2/3);
	put_img_to_img(data->image, data->minimap->cursor, data->minimap->cursor_x, data->minimap->cursor_y);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
}

void	moove_cursor(t_data *data, int direction)
{
	data->minimap->p_angle += ROTATION * direction;
	clear_image(data->minimap->direction);
	clear_image(data->minimap->raycasting);
	put_cursor_direction(data->minimap);
	put_raycasting(data->minimap, FOV, RAY_NBR, data);
	mlx_clear_window(data->display, data->window);
	put_img_to_img(data->image, data->minimap->minimap, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	put_img_to_img(data->image, data->minimap->raycasting, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	put_img_to_img(data->image, data->minimap->direction, data->minimap->cursor_x - data->minimap->pxl_size * 2/3, data->minimap->cursor_y - data->minimap->pxl_size * 2/3);
	put_img_to_img(data->image, data->minimap->cursor, data->minimap->cursor_x, data->minimap->cursor_y);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
}

int	key_handler(int key, t_data *data)
{//mettre flag azerty / qwerty modifiable
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
