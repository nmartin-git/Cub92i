/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:40:01 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/16 17:10:13 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	texture(t_data *data, const char *str)
{
	if (ft_strnstr(data->map->n_t, str, ft_strlen(data->map->n_t)))
		return (1);
	if (ft_strnstr(data->map->s_t, str, ft_strlen(data->map->s_t)))
		return (1);
	if (ft_strnstr(data->map->w_t, str, ft_strlen(data->map->w_t)))
		return (1);
	if (ft_strnstr(data->map->e_t, str, ft_strlen(data->map->e_t)))
		return (1);
	return (0);
}

void	pv_bar(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < TAB_Y / 20)
	{
		x = 0;
		while (x < TAB_X / 2)
			put_pxl(data->pv, x++, y, HEALTH_BG_COLOR);
		y++;
	}
	y = 0;
	while (y < TAB_Y / 20)
	{
		x = 0;
		while (x < (TAB_X / 2) * data->health / 100)
			put_pxl(data->pv, x++, y, HEALTH_COLOR);
		y++;
	}
}

void	loading_screen2(t_data *data, t_image *tmp, int i)
{
	if (i == 1)
		tmp->image = mlx_xpm_file_to_image(data->display,
				"tloading_screen/1.xpm", &tmp->tab_x, &tmp->tab_y);
	if (i == 2)
		tmp->image = mlx_xpm_file_to_image(data->display,
				"tloading_screen/2.xpm", &tmp->tab_x, &tmp->tab_y);
	if (i == 3)
		tmp->image = mlx_xpm_file_to_image(data->display,
				"tloading_screen/3.xpm", &tmp->tab_x, &tmp->tab_y);
	if (i == 4)
		tmp->image = mlx_xpm_file_to_image(data->display,
				"tloading_screen/4.xpm", &tmp->tab_x, &tmp->tab_y);
	if (i == 5)
		tmp->image = mlx_xpm_file_to_image(data->display,
				"tloading_screen/5.xpm", &tmp->tab_x, &tmp->tab_y);
	if (i == 6)
		tmp->image = mlx_xpm_file_to_image(data->display,
				"tloading_screen/golem.xpm", &tmp->tab_x, &tmp->tab_y);
	if (!tmp->image)
		cub_exit(1, "loading screen failed to load", data);
	mlx_put_image_to_window(data->display, data->window, tmp->image, (TAB_X
			- tmp->tab_x) / 2, (TAB_Y - tmp->tab_y) / 2);
	mlx_destroy_image(data->display, tmp->image);
}

void	loading_screen(t_data *data)
{
	int		i;
	t_image	tmp;

	srand(time(0));
	i = (rand() % 6) + 1;
	if (texture(data, "bassem"))
	{
		tmp.image = mlx_xpm_file_to_image(data->display,
				"tloading_screen/bassem.xpm", &tmp.tab_x, &tmp.tab_y);
		i = 0;
	}
	else if (texture(data, "metro"))
	{
		tmp.image = mlx_xpm_file_to_image(data->display,
				"tloading_screen/metro.xpm", &tmp.tab_x, &tmp.tab_y);
		data->map->c_rgb = -13;
		data->map->d_t = ft_strdup("textures/metrodoors.xpm");
		i = 0;
	}
	if (texture(data, "walid"))
	{
		data->map->c_rgb = -14;
		data->map->f_rgb = -10;
	}
	loading_screen2(data, &tmp, i);
}
