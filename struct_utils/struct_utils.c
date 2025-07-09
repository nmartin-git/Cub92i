/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:56:02 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/14 15:00:01 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_utils.h"

t_image	*new_image(void *display, int tab_x, int tab_y)
{
	int		end;
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (!image)
		return (write(2, "Cub92i: T_image malloc failed\n", 30), NULL);
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
	image->tab_x = tab_x;
	image->tab_y = tab_y;
	return (image);
}

void	free_image(t_image *image, void *display)
{
	if (image)
	{
		if (image->image && display)
			mlx_destroy_image(display, image->image);
		free(image);
	}
}
