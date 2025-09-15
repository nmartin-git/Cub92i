/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_item.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:49:26 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/15 16:58:38 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	display_item(t_data *data, t_wall tmp, t_pos start, t_image *texture)
{
	int	color;

	while (++(tmp.dx) < tmp.draw_w)
	{
		tmp.dy = -1;
		while (++(tmp.dy) < tmp.draw_h)
		{
			tmp.tex_x = tmp.dx / tmp.hauteur;
			tmp.tex_y = tmp.dy / tmp.hauteur;
			tmp.pixel.x = start.x + tmp.dx;
			tmp.pixel.y = start.y + tmp.dy;
			if (tmp.pixel.x < 0 || tmp.pixel.x >= TAB_X || tmp.pixel.y < 0
				|| tmp.pixel.y >= TAB_Y)
				continue ;
			color = get_pixel_color(texture, tmp.tex_x, tmp.tex_y);
			if (color == (int)0xFF000000)
				continue ;
			pixel_put(data->image, tmp.pixel, color);
		}
	}
}

void	item_on_map(t_data *data, int item, float pos, double qlqchose)
{
	t_image	*texture;
	t_wall	tmp;
	t_pos	start;
	float	tmp_bounce;

	if (item == MORDJENE)
		texture = data->texture_mordjene;
	if (item == PUFF)
		texture = data->texture_puff;
	tmp.hauteur = (((TAB_X / 2.0f) / (float)texture->tab_x) * ((MINIMAP_SIZE
					/ data->scale) / qlqchose)) / 4;
	tmp.draw_w = texture->tab_x * tmp.hauteur;
	tmp.draw_h = texture->tab_y * tmp.hauteur;
	tmp_bounce = data->bounce_y * tmp.draw_h / 200.0;
	start.x = TAB_X * pos / 100 - (tmp.draw_w / 2);
	start.y = TAB_Y / 2 + tmp_bounce;
	tmp.dx = -1;
	display_item(data, tmp, start, texture);
}

void	set_item_rayscast(t_data *data)
{
	t_pos	pos;

	pos.y = 0;
	while (pos.y < data->mmap->y)
	{
		pos.x = 0;
		while (pos.x < data->mmap->x)
		{
			if (data->map->map[pos.y][pos.x] == MORDJENE
				|| data->map->map[pos.y][pos.x] == PUFF)
				item_raycast(data, pos, data->map->map[pos.y][pos.x]);
			pos.x++;
		}
		pos.y++;
	}
}
