/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:56:02 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/06 17:01:51 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_utils.h"

t_image	*newImage(void *display, int tab_x, int tab_y)
{
	int		end;
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (!image)
	{
		write(2, "Cub92i: T_image malloc failed\n", 30);
		return (NULL);
	}
	image->image = mlx_new_image(display, tab_x, tab_y);
	if (!image->image)
	{
		write(2, "Cub92i: Image initialization failed\n", 36);
		return (free(image), NULL);
	}
	image->adress = mlx_get_data_addr(image->image,
										&image->bpp, &image->l_len, &end);
	if (!image->adress)
	{
		write(2, "Cub92i: Adress initialization failed\n", 37);
		mlx_destroy_image(display, image->image);
		return (free(image), NULL);
	}
	return (image);
}

void	freeImage(t_image *image, void *display)
{
	if (image)
	{
		if (image->image && display)
			mlx_destroy_image(display, image->image);
		free(image);
	}
}