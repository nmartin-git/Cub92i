/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:56 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/09 15:03:33 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	close_window(t_data *data)
{
	cub_exit(0, "Window closed successfully", data);
	return (0);
}

void	set_data(t_data *data, t_map *map)
{
	data->minimap = NULL;
	data->map = map;
	data->display = mlx_init();
	if (!data->display)
		cub_exit(1, "Display initialization failed", data);
	data->window = mlx_new_window(data->display, TAB_X, TAB_Y, "Cub92i");
	if (!data->window)
		cub_exit(1, "Window initialization failed", data);
	data->image = newImage(data->display, TAB_X, TAB_Y);

	int		x;//TODO enlever fond blanc
	int		y;
	char	*pxl;

	for (y = 0; y < TAB_Y; y++)
	{
		for (x = 0; x < TAB_X; x++)
		{
			pxl = data->image->adress + (y * data->image->l_len + x * (data->image->bpp / 8));
			*(unsigned int *)pxl = 0xFFFFFF; // blanc
		}
	}

}

int	minimap(t_data *data)
{
	data->minimap = malloc(sizeof(t_minimap));
	//if (!data->minimap)//TODO gerer lerreur
	minimapData(data->minimap, data);
	minimapCreate(data->minimap, data->map->map);
	return (0);
}

void	game(t_data *data, t_map *map)
{
	//set map, x et y
	set_data(data, map);
	minimap(data);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
	mlx_put_image_to_window(data->display, data->window, data->minimap->minimap->image, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	mlx_put_image_to_window(data->display, data->window, data->minimap->cursor->image, data->minimap->cursor_x, data->minimap->cursor_y);
	mlx_key_hook(data->window, key_handler, data);
	mlx_hook(data->window, 17, 1L >> 0, close_window, data);
	mlx_loop(data->display);
	free_data(data);
}