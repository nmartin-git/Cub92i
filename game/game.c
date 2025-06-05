/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:56 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/05 16:07:35 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	close_window(t_data *data)
{
	cub_exit(0, "Window closed successfully", data);
	return (0);
}

int	key_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		cub_exit(0, "Window closed successfully", data);
	return (0);
}

void	set_data(t_data *data, t_map *map)
{
	int		bpp;
	int		l_len;
	int		end;

	data->minimap = NULL;
	data->map = map;
	data->display = mlx_init();
	if (!data->display)
		cub_exit(1, "Display initialization failed", data);
	data->window = mlx_new_window(data->display, TAB_X, TAB_Y, "cub");
	if (!data->window)
		cub_exit(1, "Window initialization failed", data);
	data->image = mlx_new_image(data->display, TAB_X, TAB_Y);
	if (!data->image)
		cub_exit(1, "Image initialization failed", data);
	data->adress = mlx_get_data_addr(data->image, &bpp, &l_len, &end);
	if (!data->adress)
		cub_exit(1, "Adress initialization failed", data);
	data->bpp = bpp;
	data->l_len = l_len;
}

int	minimap(t_data *data)
{
	data->minimap = malloc(sizeof(t_minimap));
	//if (!data->minimap)//TODO gerer lerreur
	minimapData(data->minimap, data->display, data->map->col, data->map->row);
	minimapCreate(data->minimap, data->map->map);
	return (0);
}

void	game(t_data *data, t_map *map)
{
	//set map, x et y
	set_data(data, map);
	minimap(data);
	mlx_put_image_to_window(data->display, data->window, data->image, 0, 0);
	mlx_put_image_to_window(data->display, data->window, data->minimap->image, 0, 0);
	mlx_key_hook(data->window, key_handler, data);
	mlx_hook(data->window, 17, 1L >> 0, close_window, data);
	mlx_loop(data->display);
	free_data(data);
}