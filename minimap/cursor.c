/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:17:16 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/06 18:05:36 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	mooveCursor(t_data *data, int plus, int *value)
{//TODO gerer collision mur
	if (plus)
		*value += 10;
	else
		*value -= 10;
}

void	pixelPutCursor(t_image *cursor, int color, int width, int height)
{
	char	*pxl;
	int		x;
	int		y;
	int		dx;
	int		dy;

	y = 0;
	while (y < height)
	{//TODO faire la meme couleur a chque fois ptet et faire degrade
		x = 0;
		while (x < width)
		{
			dx = x - CURSOR_RADIUS;
			dy = y - CURSOR_RADIUS;
			if (dx * dx + dy * dy <= CURSOR_RADIUS * CURSOR_RADIUS)
			{
				pxl = cursor->adress +
					(y * cursor->l_len + x * (cursor->bpp / 8));
				*(unsigned int *)pxl = color;
			}
			x++;
		}
		y++;
	}
}
