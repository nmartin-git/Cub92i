/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:24:31 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/18 18:10:24 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_utils.h"

int	open_xpm(t_data *data, t_image *texture, int state)
{
	char	*str;
	int		nul;

	if (state == 1)
		str = data->map->n_t;
	if (state == 2)
		str = data->map->s_t;
	if (state == 3)
		str = data->map->e_t;
	if (state == 4)
		str = data->map->w_t;
	texture->image = mlx_xpm_file_to_image(data->display, str, &texture->tab_x,
			&texture->tab_y);
	if (!texture->image)
		return (1);
	texture->adress = mlx_get_data_addr(texture->image, &texture->bpp,
			&texture->l_len, &nul);
	if (!texture->adress)
		return (2);
	return (0);
}

int	load_texutres(t_data *data)
{
	if (open_xpm(data, data->texture_n, 1))
		return (write(2, "Error\nFail to load N texture\n", 29));
	if (open_xpm(data, data->texture_s, 2))
		return (write(2, "Error\nFail to load S texture\n", 29));
	if (open_xpm(data, data->texture_e, 3))
		return (write(2, "Error\nFail to load S texture\n", 29));
	if (open_xpm(data, data->texture_w, 4))
		return (write(2, "Error\nFail to load S texture\n", 29));
	return (0);
}

void	free_textures(t_data *data)
{
	if (data->texture_n)
		free_image(data->texture_n, data->display);
	if (data->texture_s)
		free_image(data->texture_s, data->display);
	if (data->texture_e)
		free_image(data->texture_e, data->display);
	if (data->texture_w)
		free_image(data->texture_w, data->display);
}
