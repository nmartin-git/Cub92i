/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:59:29 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/10 20:19:15 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minimap.h"

void	pixel_put(t_image *raycasting, t_pos pixel, int color)
{
	char	*pxl;
	int		b;

	b = raycasting->bpp;
	if (pixel.x >= 0 && pixel.x <= raycasting->tab_x && pixel.y >= 0 && pixel.y <= raycasting->tab_y)
	{
		pxl = raycasting->adress + (pixel.y * raycasting->l_len + pixel.x * (b / 8));
		*(unsigned int *)pxl = color;
	}
}

void	small_angle(t_image *raycasting, t_pos pixel, int dx, int dy)
{
	int	i;
	int	decision;

	i = 0;
	decision = 2 * ft_abs(dy) - ft_abs(dx);
	pixel_put(raycasting, pixel, 11111111);
	while (i++ < ft_abs(dx))
	{
		if (dx > 0)
			pixel.x++;
		else
			pixel.x--;
		if (decision < 0)
			decision += 2 * ft_abs(dy);
		else
		{
			decision += 2 * ft_abs(dy) - 2 * ft_abs(dx);
			if (dy > 0)
				pixel.y++;
			else
				pixel.y--;
		}
		pixel_put(raycasting, pixel, 11111111);
	}
}

void	big_angle(t_image *raycasting, t_pos pixel, int dx, int dy)
{
	int	i;
	int	decision;

	i = 0;
	decision = 2 * ft_abs(dx) - ft_abs(dy);
	pixel_put(raycasting, pixel, 11111111);
	while (i++ < ft_abs(dy))
	{
		if (dy > 0)
			pixel.y++;
		else
			pixel.y--;
		if (decision < 0)
			decision += 2 * ft_abs(dx);
		else
		{
			decision += 2 * ft_abs(dx) - 2 * ft_abs(dy);
			if (dx > 0)
				pixel.x++;
			else
				pixel.x--;
		}
		pixel_put(raycasting, pixel, 11111111);
	}
}

void	put_line(t_minimap *minimap, int x, int y)
{	
	int		dx;
	int		dy;
	t_pos	point_a;
	
	point_a.x = minimap->cursor_x + minimap->squareSize / 3 - MINIMAP_SIZE / 15;
	point_a.y = minimap->cursor_y + minimap->squareSize / 3 - MINIMAP_SIZE / 15;
	dx = x - point_a.x;
	dy = y - point_a.y;
	if (ft_abs(dx) > ft_abs(dy))
		small_angle(minimap->raycasting, point_a, dx, dy);
	else
		big_angle(minimap->raycasting, point_a, dx, dy);
}

void	putCursorDirection(t_minimap *minimap)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	t_pos	point_a;
	
	point_a.x = minimap->direction->tab_x / 2;
	point_a.y = minimap->direction->tab_y / 2;
	x = point_a.x + cos(minimap->p_angle) * minimap->squareSize;
	y = point_a.y + sin(minimap->p_angle) * minimap->squareSize;
	dx = x - point_a.x;
	dy = y - point_a.y;
	if (ft_abs(dx) > ft_abs(dy))
		small_angle(minimap->direction, point_a, dx, dy);
	else
		big_angle(minimap->direction, point_a, dx, dy);
}
