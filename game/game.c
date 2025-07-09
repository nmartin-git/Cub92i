/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:56 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/09 15:36:33 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//TODO gerer les erreurs de new_image (tout free)
int	close_window(t_data *data)
{
	cub_exit(0, "Window closed successfully", data);
	return (0);
}

void	set_data(t_data *data, t_map *map)
{
	data->health = HEALTH;
	data->minimap = NULL;
	data->pv = NULL;
	data->map = map;
	data->display = mlx_init();
	if (!data->display)
		cub_exit(1, "Display initialization failed", data);
	data->window = mlx_new_window(data->display, TAB_X, TAB_Y, "Cub92i");
	if (!data->window)
		cub_exit(1, "Window initialization failed", data);
	data->image = new_image(data->display, TAB_X, TAB_Y);
}

int	minimap(t_data *data)
{
	data->minimap = malloc(sizeof(t_minimap));
	//if (!data->minimap)//TODO gerer lerreur
	minimap_data(data->minimap, data);
	minimap_create(data->minimap, data);
	return (0);
}

void	pv_bar(t_data *data)
{
	char	*pxl;
	int		b;
	int		l;
	int		x;
	int		y;

	data->pv = new_image(data->display, TAB_X / 2, TAB_Y / 20);
	b = data->pv->bpp;
	l = data->pv->l_len;
	y = 0;
	while (y < TAB_Y / 20)
	{
		x = 0;
		while (x < TAB_X / 2)
		{
			pxl = data->pv->adress + (y * l + x * (b / 8));
			*(unsigned int *)pxl = HEALTH_BG_COLOR;
			x++;
		}
		y++;
	}
	y = 0;
	while (y < TAB_Y / 20)
	{
		x = 0;
		while (x < (TAB_X / 2) * data->health / 100)
		{
			pxl = data->pv->adress + (y * l + x * (b / 8));
			*(unsigned int *)pxl = HEALTH_COLOR;
			x++;
		}
		y++;
	}
}

void	game(t_data *data, t_map *map)
{
	set_data(data, map);
	minimap(data);
	pv_bar(data);
	//loading screen ?
	put_img_to_img(data->image, data->minimap->minimap, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	put_img_to_img(data->image, data->minimap->raycasting, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	put_img_to_img(data->image, data->minimap->direction, data->minimap->cursor_x - data->minimap->pxl_size * 2/3, data->minimap->cursor_y - data->minimap->pxl_size * 2/3);
	put_img_to_img(data->image, data->minimap->cursor, data->minimap->cursor_x, data->minimap->cursor_y);
	put_img_to_img(data->image, data->pv, TAB_X / 4, TAB_Y - TAB_Y / 6);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
	// mlx_put_image_to_window(data->display, data->window, data->minimap->minimap->image, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	// mlx_put_image_to_window(data->display, data->window, data->minimap->raycasting->image, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	// mlx_put_image_to_window(data->display, data->window, data->minimap->direction->image, data->minimap->cursor_x - data->minimap->squareSize * 2/3, data->minimap->cursor_y - data->minimap->squareSize * 2/3);
	// mlx_put_image_to_window(data->display, data->window, data->minimap->cursor->image, data->minimap->cursor_x, data->minimap->cursor_y);
	mlx_key_hook(data->window, key_handler, data);
	mlx_hook(data->window, 17, 1L >> 0, close_window, data);
	mlx_loop(data->display);
	free_data(data);
}
