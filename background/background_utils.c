/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:35:27 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/07 19:15:04 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/background.h"

int	decode_r(int rgb)
{
	return ((rgb >> 16) & 255);
}

int	decode_g(int rgb)
{
	return ((rgb >> 8) & 255);
}

int	decode_b(int rgb)
{
	return (rgb & 255);
}

void	init_image(t_image *img)
{
	img->image = NULL;
	img->adress = NULL;
	img->bpp = -1;
	img->l_len = -1;
	img->tab_x = -1;
	img->tab_y = -1;
}
