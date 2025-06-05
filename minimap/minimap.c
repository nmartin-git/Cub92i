/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:23:31 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/05 16:20:24 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	setMinimapColor(t_minimap *minimap)
{
	//TODO faire des presets ou un bail de random colors
	minimap->p_color = 555555;
	minimap->w_color = 666666;
	minimap->f_color = 777777;
	minimap->b_color = 999999;
}

int	getMinimapColor(t_minimap *minimap, int content)
{//TODO ptet ajouter couleur de checkpoint, boss, el mordjene, puff
	if (content == WALL)
		return (minimap->w_color);
	else if (content == EMPTY)
		return (minimap->b_color);
	else
		return (minimap->f_color);
}

void	minimapData(t_minimap *minimap, void *display, int x, int y)
{
	int		bpp;
	int		l_len;
	int		end;

	setMinimapColor(minimap);
	minimap->display = display;
	minimap->image = mlx_new_image(minimap->display, MINIMAP_SIZE, MINIMAP_SIZE);
	// if (!minimap->image)
	// 	cub_exit(1, "Image initialization failed", data);//TODO gerer les leaks en cas derreurs
	minimap->adress = mlx_get_data_addr(minimap->image, &bpp, &l_len, &end);
	// if (!minimap->adress)
	// 	cub_exit(1, "Adress initialization failed", data);//TODO gerer les leaks en cas derreurs
	minimap->bpp = bpp;
	minimap->l_len = l_len;
	minimap->x = x;
	minimap->y = y;
	if (minimap->x > minimap->y)
		minimap->squareSize = MINIMAP_SIZE / minimap->x;
	else
		minimap->squareSize = MINIMAP_SIZE / minimap->y;
}

void	pixelPutSquare(t_minimap *minimap, t_pos pixel, int color)
{
	char	*pxl;
	int		b;
	int		l;
	int		x;
	int		i;
	int		y;

	b = minimap->bpp;
	l = minimap->l_len;
	x = pixel.x * minimap->squareSize;
	pixel.y *= minimap->squareSize;
	y = 0;
	while (y < minimap->squareSize)
	{
		i = 0;
		pixel.x = x;
		while (i < minimap->squareSize)
		{
			if (pixel.x >= 0 && pixel.x <= MINIMAP_SIZE
				&& pixel.y >= 0 && pixel.y <= MINIMAP_SIZE)
			{
				pxl = minimap->adress + (pixel.y * l + pixel.x * (b / 8));
				*(unsigned int *)pxl = color;
			}
			pixel.x++;
			i++;
		}
		pixel.y++;
		y++;
	}
}

void	minimapCreate(t_minimap *minimap, int **map)
{
	t_pos	pixel;
	int		color;

	pixel.y = 0;
	while (pixel.y < minimap->y + 2)//TODO tej les +2 qd parsing updated
	{
		pixel.x = 0;
		while (pixel.x < minimap->x + 2)//TODO tej les +2 qd parsing updated
		{
			color = getMinimapColor(minimap, map[pixel.y][pixel.x]);
			pixelPutSquare(minimap, pixel, color);
			pixel.x++;
		}
		pixel.y++;
	}
}
