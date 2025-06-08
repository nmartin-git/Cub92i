/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easter_eggs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:44:50 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/08 21:46:03 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/background.h"

int	easter_egg(t_image *img, t_data *data)
{
	t_image	new;
	int		null;

	init_image(&new);
	if (data->map->c_rgb == -10)
		new.image = mlx_xpm_file_to_image(data->display, "./test.xpm", &new.w,
				&new.h);
	else if (data->map->c_rgb == -11)
		new.image = mlx_xpm_file_to_image(data->display, "./tt.xpm", &new.w,
				&new.h);
	else if (data->map->c_rgb == -12)
		new.image = mlx_xpm_file_to_image(data->display, "./tt.xpm", &new.w,
				&new.h);
	if (!new.image)
		return (write(2, "Error\nFail to init\n", 19));
	new.adress = mlx_get_data_addr(new.image, &new.bpp, &new.l_len, &null);
	if (!new.adress)
	{
		mlx_destroy_image(data->display, new.image);
		return (free(new.image), write(2, "Error\nFail to init\n", 19));
	}
	put_img_to_img(img, &new, 0, 0);
	mlx_destroy_image(data->display, new.image);
	return (0);
}
