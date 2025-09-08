/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:23:31 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/09 00:47:42 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	set_minimap_color(t_minimap *minimap)
{
	minimap->p_color = 555555;
	minimap->w_color = 666666;
	minimap->f_color = 777777;
	minimap->b_color = 999999;
	minimap->c_color = 888888;
}

int	get_minimap_color(t_minimap *minimap, int content)
{
	if (content == WALL)
		return (minimap->w_color);
	else if (content == EMPTY)
		return (minimap->b_color);
	else
		return (minimap->f_color);
}

void	minimap_data(t_minimap *minimap, t_data *data, int size)
{
	set_minimap_color(minimap);
	minimap->x = data->map->col;
	minimap->y = data->map->row;
	if (minimap->x > minimap->y)
		minimap->pxl_size = size / minimap->x;
	else
		minimap->pxl_size = size / minimap->y;
	minimap->cursor_x = data->map->x_spawn * minimap->pxl_size + size / 15 + \
		minimap->pxl_size / 6;
	minimap->cursor_y = data->map->y_spawn * minimap->pxl_size + size / 15 + \
		minimap->pxl_size / 6;
	if (data->map->map[data->map->y_spawn][data->map->x_spawn] == E_DIR)
		minimap->p_angle = 0;
	else if (data->map->map[data->map->y_spawn][data->map->x_spawn] == N_DIR)
		minimap->p_angle = 3 * PI / 2;
	else if (data->map->map[data->map->y_spawn][data->map->x_spawn] == W_DIR)
		minimap->p_angle = PI;
	else
		minimap->p_angle = PI / 2;
	minimap->sb15 = size / 15;
	minimap->display = data->display;
	minimap->scale = (float)(MINIMAP_SIZE / SCREEN_MINIMAP_SIZE);
	if (load_image(minimap, data))
		cub_exit(1, "Image failed to load", data);
}

void	minimap_create(t_minimap *minimap, t_data *data)
{
	t_pos	pixel;
	int		color;

	pixel.y = 0;
	while (pixel.y < minimap->y)
	{
		pixel.x = 0;
		while (pixel.x < minimap->x)
		{
			color = get_minimap_color(minimap, \
				data->map->map[pixel.y][pixel.x]);
			pixel_put_square(minimap, pixel, color);
			if (data->map->map[pixel.y][pixel.x] == MORDJENE)
				put_mordjene(minimap, pixel, minimap->pxl_size / 3, \
					minimap->pxl_size / 4);
			else if (data->map->map[pixel.y][pixel.x] == PUFF)
				put_puff(minimap, pixel, minimap->pxl_size / 3, \
					minimap->pxl_size * 3 / 4);
			pixel.x++;
		}
		pixel.y++;
	}
	pixel_put_cursor(minimap->cursor, minimap->c_color, minimap->pxl_size / \
		1.5, minimap->pxl_size / 3);
}
