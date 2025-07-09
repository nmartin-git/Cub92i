/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:35:27 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/08 21:44:29 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/background.h"

/*
renvoie le rouge du rgb encodé
*/

int	decode_r(int rgb)
{
	return ((rgb >> 16) & 255);
}

/*
renvoie le vert du rgb encodé
*/

int	decode_g(int rgb)
{
	return ((rgb >> 8) & 255);
}

/*
renvoie le bleu du rgb encodé
*/

int	decode_b(int rgb)
{
	return (rgb & 255);
}

/*
initialise l'image
*/

void	init_image(t_image *img)
{
	img->image = NULL;
	img->adress = NULL;
	img->bpp = -1;
	img->l_len = -1;
}
