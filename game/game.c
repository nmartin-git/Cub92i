/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:45:56 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/10 03:47:54 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	set_image_to_null(t_data *data)
{
	data->background->image = NULL;
	data->texture_n->image = NULL;
	data->texture_s->image = NULL;
	data->texture_e->image = NULL;
	data->texture_w->image = NULL;
	if (data->map->doors)
		data->texture_door->image = NULL;
	data->pv = NULL;
}

void	set_data(t_data *data, t_map *map)
{
	int	i;

	i = -1;
	data->health = HEALTH - 40;
	data->map = map;
	data->display = mlx_init();
	if (!data->display)
		cub_exit(1, "Display initialization failed", data);
	data->window = mlx_new_window(data->display, TAB_X, TAB_Y, "Cub92i");
	if (!data->window)
		cub_exit(1, "Window initialization failed", data);
	data->image = new_image(data->display, TAB_X, TAB_Y);
	if (!data->image)
		cub_exit(1, "Malloc fail\n", data);
	loading_screen(data);
	data->background = ft_calloc(sizeof(t_image), 1);
	if (!data->background)
		cub_exit(1, "Malloc fail\n", data);
	if (init_textures(data))
		cub_exit(1, "Malloc fail\n", data);
	set_image_to_null(data);
	while (++i < 10)
		data->keys[i] = 0;
}

int	minimap(t_data *data)
{
	data->mmap = malloc(sizeof(t_minimap));
	data->sc_mmap = malloc(sizeof(t_minimap));
	minimap_data(data->mmap, data, MINIMAP_SIZE);
	minimap_data(data->sc_mmap, data, SCREEN_MINIMAP_SIZE);
	minimap_create(data->mmap, data);
	minimap_create(data->sc_mmap, data);
	return (0);
}

int	render(t_data *data)
{
	static __uint64_t	last_time = 0;
	__uint64_t			now;
	__uint64_t			delta_time;

	now = get_time_ms();
	delta_time = now - last_time;
	if (delta_time < 16)
	{
		usleep((16 - delta_time) * 1000);
		now = get_time_ms();
		delta_time = now - last_time;
	}
	last_time = now;
	if (delta_time < 200 && delta_time > 0)
		update(data, delta_time);
	put_cursor_direction(data->sc_mmap, data->mmap->p_angle);
	put_img_to_img(data->image, data->background, 0, 0);
	put_raycasting(data->mmap, FOV, TAB_X, data);
	put_img_to_img(data->image, data->crosshair->cross_img, \
		data->crosshair->pos_c_x, data->crosshair->pos_c_y);
	put_img_to_img(data->image, data->sc_mmap->minimap, \
		SCREEN_MINIMAP_SIZE / 15, SCREEN_MINIMAP_SIZE / 15);
	put_img_to_img(data->image, data->sc_mmap->direction, \
		data->sc_mmap->cursor_x - data->sc_mmap->pxl_size / 1.5, \
		data->sc_mmap->cursor_y - data->sc_mmap->pxl_size / 1.5);
	put_img_to_img(data->image, data->sc_mmap->cursor, \
		data->sc_mmap->cursor_x, data->sc_mmap->cursor_y);
	put_img_to_img(data->image, data->pv, TAB_X / 4, TAB_Y - TAB_Y / 6);
	mlx_put_image_to_window(data->display, data->window, \
		data->image->image, 0, 0);
	return (0);
}

void	game(t_data *data, t_map *map)
{
	set_data(data, map);
	if (init_crosshair(data))
		cub_exit(1, "Crosshair failed to load", data);
	if (load_texutres(data))
		cub_exit(1, "Texture failed to load", data);
	if (minimap(data))
		cub_exit(1, "Minimap failed to load", data);
	data->pv = new_image(data->display, TAB_X / 2, TAB_Y / 20);
	if (!data->pv)
		cub_exit(1, "", data);
	pv_bar(data);
	// mlx_mouse_hide_no_leak(data->display, data->window);
	if (paint_floor_and_ceiling(data->background, data))
		cub_exit(1, "", data);
	mlx_put_image_to_window(data->display, data->window, \
		data->image->image, 0, 0);
	mlx_hook(data->window, 6, (1L << 6), &mouse_move, data);
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_hook(data->window, 3, 1L << 1, key_release, data);
	mlx_hook(data->window, 17, 1L >> 0, close_window, data);
	mlx_mouse_hook(data->window, mouse_hook, data);
	mlx_loop_hook(data->display, &render, data);
	mlx_loop(data->display);
	free_data(data);
}
