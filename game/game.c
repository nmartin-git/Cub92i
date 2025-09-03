/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:56 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/20 17:07:52 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <sys/time.h>

int	close_window(t_data *data)
{
	cub_exit(0, "Window closed successfully", data);
	return (0);
}

int		init_textures(t_data *data)
{
	data->texture_n = malloc(sizeof(t_image));
	if	(!data->texture_n)
		return (1);
	data->texture_s = malloc(sizeof(t_image));
	if	(!data->texture_s)
		return (free(data->texture_n), 1);
	data->texture_e = malloc(sizeof(t_image));
	if	(!data->texture_e)
		return (free(data->texture_n), free(data->texture_s), 1);
	data->texture_w = malloc(sizeof(t_image));
	if	(!data->texture_w)
		return (free(data->texture_n), free(data->texture_s), \
				free(data->texture_e), 1);
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
	if	(!data->image)
		cub_exit(1, "Malloc fail\n", data);
	data->background = malloc(sizeof(t_image));
	if (!data->background)
		cub_exit(1, "Malloc fail\n", data);		
	if (init_textures(data))
		cub_exit(1, "Malloc fail\n", data);	
	for (size_t i = 0; i < 10; i++)
		data->keys[i] = 0;	
}

int	minimap(t_data *data)
{
	data->minimap = malloc(sizeof(t_minimap));
	//if (!data->minimap)//TODO gerer lerreur
	minimap_data(data->minimap, data);
	minimap_create(data->minimap, data);
	return (0);
}

__uint64_t get_time_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (__uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int render(t_data *data)
{
	static __uint64_t last_time = 0;
	static __uint64_t last_fps_time = 0;
	static int frame_count = 0;
	__uint64_t		now = get_time_ms();
	__uint64_t	delta_time = now - last_time;

	if (delta_time < 16)
	{
		usleep((16 -  delta_time) * 1000);
		now = get_time_ms();
		delta_time = now - last_time; 
	}
	last_time = now;
	
	update(data, delta_time);
	// put_cursor_direction(data->minimap);
	put_img_to_img(data->image, data->background, 0, 0);
	put_raycasting(data->minimap, FOV, TAB_X, data);
	put_img_to_img(data->image, data->crosshair->cross_img, data->crosshair->pos_c_x, data->crosshair->pos_c_y);
	// put_img_to_img(data->image, data->minimap->minimap, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	// put_img_to_img(data->image, data->minimap->raycasting, MINIMAP_SIZE / 15, MINIMAP_SIZE / 15);
	// put_img_to_img(data->image, data->minimap->direction, data->minimap->cursor_x - data->minimap->pxl_size * 2/3, data->minimap->cursor_y - data->minimap->pxl_size * 2/3);
	// put_img_to_img(data->image, data->minimap->cursor, data->minimap->cursor_x, data->minimap->cursor_y);
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
	frame_count++;
	if (now - last_fps_time >= 1000)
	{
		printf("FPS : %d\n", frame_count);
		frame_count = 0;
		last_fps_time = now;
	}
	last_time = now;
	return (0);
}



void	game(t_data *data, t_map *map)
{
	set_data(data, map);
	if (init_crosshair(data))
		exit(1);
	if (load_texutres(data))
		exit(1);
	minimap(data);
	// loading screen ?
	// mlx_mouse_hide_no_leak(data->display, data->window);
	if (paint_floor_and_ceiling(data->background, data))
	{
		free_data(data);
		exit(1);
	}
	mlx_put_image_to_window(data->display, data->window, data->image->image, 0, 0);
	mlx_hook(data->window, 6, (1L<<6), &mouse_move, data);
	mlx_hook(data->window, 2, 1L<<0, key_press, data);
	mlx_hook(data->window, 3, 1L<<1, key_release, data);
	mlx_hook(data->window, 17, 1L >> 0, close_window, data);
	mlx_loop_hook(data->display, &render, data);
	mlx_loop(data->display);
	free_data(data);
}
