/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:06 by nmartin           #+#    #+#             */
/*   Updated: 2025/07/09 14:27:54 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

// void	put_puffs(t_image *minimap, t_pos *pos, int size, int radius)
// {
// 	char	*pxl;
// 	int		x;
// 	int		y;
// 	int		dx;
// 	int		dy;

// 	y = 0;
// 	while (y < size)
// 	{//TODO faire la meme couleur a chque fois ptet et faire degrade
// 		x = 0;
// 		while (x < size)
// 		{
// 			dx = x - radius;
// 			dy = y - radius;
// 			if (dx * dx + dy * dy <= radius * radius)
// 			{
// 				pxl = minimap->adress +
// 					(y * minimap->l_len + x * (minimap->bpp / 8));
// 				*(unsigned int *)pxl = PUFF_COLOR;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	put_mordjene(t_image *minimap, t_pos *pos, int size, int radius)
// {
// 	char	*pxl;
// 	int		x;
// 	int		y;
// 	int		dx;
// 	int		dy;

// 	y = 0;
// 	while (y < size)
// 	{//TODO faire la meme couleur a chque fois ptet et faire degrade
// 		x = 0;
// 		while (x < size)
// 		{
// 			dx = x - radius;
// 			dy = y - radius;
// 			if (dx * dx + dy * dy <= radius * radius)
// 			{
// 				pxl = minimap->adress +
// 					(y * minimap->l_len + x * (minimap->bpp / 8));
// 				*(unsigned int *)pxl = MORDJENE_COLOR;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	is_puff()
// {
	
// }
