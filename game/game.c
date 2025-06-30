/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:56 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/30 19:49:48 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <sys/time.h>

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
	data->image = new_image(data->display, TAB_X, TAB_Y);
	data->game = new_image(data->display, TAB_X, TAB_Y);
	data->background = new_image(data->display, TAB_X, TAB_Y);
	if (paint_floor_and_ceiling(data->background, data))
	{
		free_data(data);
		exit(1);
	}
	// int		x;//TODO enlever fond blanc
	// int		y;
	// char	*pxl;

	// for (y = 0; y < TAB_Y; y++)
	// {
	// 	for (x = 0; x < TAB_X; x++)
	// 	{
	// 		pxl = data->image->adress + (y * data->image->l_len + x * (data->image->bpp / 8));
	// 		*(unsigned int *)pxl = 0xFFFFFF; // blanc
	// 	}
	// }

}

int	minimap(t_data *data)
{
	data->minimap = malloc(sizeof(t_minimap));
	//if (!data->minimap)//TODO gerer lerreur
	minimap_data(data->minimap, data);
	minimap_create(data->minimap, data);
	return (0);
}
#include <sys/time.h>

__uint64_t get_time_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (__uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int render(t_data *data)
{
	static __uint64_t last_fps_time = 0;
	static int frame_count = 0;
	__uint64_t		now = get_time_ms();

	memset(data->minimap->direction->adress, 0, data->minimap->direction->tab_y * data->minimap->direction->l_len);
	memset(data->minimap->raycasting->adress, 0, data->minimap->raycasting->tab_y * data->minimap->raycasting->l_len);
	memset(data->game->adress, 0, data->game->tab_y * data->game->l_len);
	memset(data->image->adress, 0, data->image->tab_y * data->image->l_len);
	put_cursor_direction(data->minimap);
	put_raycasting(data->minimap, FOV, TAB_X, data);
	put_img_to_img(data->image, data->background, 0, 0);
	// put_img_to_img(data->image, data->minimap->minimap, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	// put_img_to_img(data->image, data->minimap->raycasting, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	// put_img_to_img(data->image, data->minimap->direction, data->minimap->cursor_x - data->minimap->pxl_size * 2/3, data->minimap->cursor_y - data->minimap->pxl_size * 2/3);
	// put_img_to_img(data->image, data->minimap->cursor, data->minimap->cursor_x, data->minimap->cursor_y);
	put_img_to_img(data->image, data->game, 0, 0);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
	frame_count++;
	if (now - last_fps_time >= 1000)
	{
		printf("FPS : %d\n", frame_count);
		frame_count = 0;
		last_fps_time = now;
	}
	// __uint64_t after = get_time_ms();
	// printf("render time = %lums\n", (after - now));
	
	return (0);
}

void	game(t_data *data, t_map *map)
{
	set_data(data, map);
	minimap(data);
	// loading screen ?
	mlx_key_hook(data->window, key_handler, data);
	mlx_hook(data->window, 17, 1L >> 0, close_window, data);
	mlx_loop_hook(data->display, &render, data);
	mlx_loop(data->display);
	free_data(data);
}
