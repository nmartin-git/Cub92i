/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:17:16 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/07 22:01:50 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

// void	_direction(t_minimap *minimap)
// {
// 	int		x;
// 	int		y;
// 	int		dx;
// 	int		dy;
// 	t_pos	point_a;

// 	point_a.x = minimap->direction->tab_x / 2;
// 	point_a.y = minimap->direction->tab_y / 2;
// 	x = point_a.x + cos(minimap->p_angle) * minimap->pxl_size;
// 	y = point_a.y + sin(minimap->p_angle) * minimap->pxl_size;
// 	dx = x - point_a.x;
// 	dy = y - point_a.y;
// 	if (ft_abs(dx) > ft_abs(dy))
// 		small_angle(minimap->direction, point_a, dx, dy);
// 	else
// 		big_angle(minimap->direction, point_a, dx, dy);
// }

void	pixel_put_cursor(t_image *cursor, int color, int size, int radius)
{
	char	*pxl;
	int		x;
	int		y;
	int		dx;
	int		dy;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			dx = x - radius;
			dy = y - radius;
			if (dx * dx + dy * dy <= radius * radius)
			{
				pxl = cursor->adress + (y * cursor->l_len + \
					x * (cursor->bpp / 8));
				*(unsigned int *)pxl = color;
			}
			x++;
		}
		y++;
	}
}
