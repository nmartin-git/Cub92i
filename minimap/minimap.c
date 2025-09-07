/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:23:31 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/07 18:35:30 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	set_minimap_color(t_minimap *minimap)
{
	//TODO faire des presets ou un bail de random colors
	minimap->p_color = 555555;
	minimap->w_color = 666666;
	minimap->f_color = 777777;
	minimap->b_color = 999999;
	minimap->c_color = 888888;
}

int	get_minimap_color(t_minimap *minimap, int content)
{
	//TODO ptet ajouter couleur de checkpoint, boss, el mordjene, puff
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
// printf("size : %d (%d)  x = %d, y = %d\n", MINIMAP_SIZE, MINIMAP_SIZE % minimap->pxl_size, MINIMAP_SIZE % minimap->x, MINIMAP_SIZE % minimap->y);
	minimap->cursor_x = data->map->x_spawn * minimap->pxl_size + size / 15 + minimap->pxl_size / 6;
	minimap->cursor_y = data->map->y_spawn * minimap->pxl_size + size / 15 + minimap->pxl_size / 6;
	// printf("[%d][%d] * %d\n", data->map->y_spawn, data->map->x_spawn, data->minimap->pxl_size);
	if (data->map->map[data->map->y_spawn][data->map->x_spawn] == E_DIR)
		minimap->p_angle = 0;
	else if (data->map->map[data->map->y_spawn][data->map->x_spawn] == N_DIR)
		minimap->p_angle = 3 * PI / 2;
	else if (data->map->map[data->map->y_spawn][data->map->x_spawn] == W_DIR)
		minimap->p_angle = PI;
	else
		minimap->p_angle = PI / 2;
	minimap->minimap_size_by_15 = size / 15;
	minimap->display = data->display;
	minimap->scale = (float)(MINIMAP_SIZE / SCREEN_MINIMAP_SIZE);
	minimap->minimap = new_image(data->display, minimap->pxl_size * minimap->x, minimap->pxl_size * minimap->y);//TODO gerer les leaks en cas derreurs
	minimap->cursor = new_image(data->display, minimap->pxl_size / 1.5, minimap->pxl_size / 1.5);//TODO gerer les leaks en cas derreurs//TODO gerer la taille du cursuer (propotionnel)
	minimap->direction = new_image(data->display, minimap->pxl_size * 2, minimap->pxl_size * 2);//TODO gerer les leaks en cas derreurs//TODO gerer la taille du cursuer (propotionnel)
	minimap->raycasting = new_image(data->display, minimap->pxl_size * minimap->x, minimap->pxl_size * minimap->y);//TODO gerer les leaks en cas derreurs//TODO gerer la taille du cursuer (propotionnel)
}

void	pixel_put_square(t_minimap *minimap, t_pos pixel, int color)
{
	char	*pxl;
	int		b;
	int		l;
	int		x;
	int		i;
	int		y;

	b = minimap->minimap->bpp;
	l = minimap->minimap->l_len;
	x = pixel.x * minimap->pxl_size;
	pixel.y *= minimap->pxl_size;
	y = 0;
	while (y < minimap->pxl_size)
	{
		i = 0;
		pixel.x = x;
		while (i < minimap->pxl_size)
		{
			if (pixel.x >= 0 && pixel.x <= minimap->minimap->tab_x
				&& pixel.y >= 0 && pixel.y <= minimap->minimap->tab_y)
			{
				pxl = minimap->minimap->adress + (pixel.y * l + pixel.x * (b / 8));
				*(unsigned int *)pxl = color;
			}
			pixel.x++;
			i++;
		}
		pixel.y++;
		y++;
	}
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
			color = get_minimap_color(minimap, data->map->map[pixel.y][pixel.x]);
			pixel_put_square(minimap, pixel, color);
			if (data->map->map[pixel.y][pixel.x] == MORDJENE)
				put_mordjene(minimap, pixel, minimap->pxl_size / 3, minimap->pxl_size / 4);
			else if (data->map->map[pixel.y][pixel.x] == PUFF)
				put_puff(minimap, pixel, minimap->pxl_size / 3, minimap->pxl_size * 3 / 4);
			pixel.x++;
		}
		pixel.y++;
	}
	pixel_put_cursor(minimap->cursor, minimap->c_color, minimap->pxl_size / 1.5, minimap->pxl_size / 3);
}
