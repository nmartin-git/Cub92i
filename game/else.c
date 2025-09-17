/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:40:01 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/17 16:37:13 by nmartin          ###   ########.fr       */
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

static inline void	load_img(t_data *data, t_image *tmp, char *path)
{
	if (convert_xpm(path, TAB_X, TAB_Y))
	{
		tmp->image = NULL;
		return ;
	}
	tmp->image = mlx_xpm_file_to_image(data->display, path, &tmp->tab_x,
			&tmp->tab_y);
}

void	loading_screen2(t_data *data, t_image *tmp, int i)
{
	if (i == 1)
		load_img(data, tmp, "tloading_screen/1.xpm");
	if (i == 2)
		load_img(data, tmp, "tloading_screen/2.xpm");
	if (i == 3)
		load_img(data, tmp, "tloading_screen/3.xpm");
	if (i == 4)
		load_img(data, tmp, "tloading_screen/4.xpm");
	if (i == 5)
		load_img(data, tmp, "tloading_screen/5.xpm");
	if (i == 6)
		load_img(data, tmp, "tloading_screen/golem.xpm");
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
		load_img(data, &tmp, "tloading_screen/bassem.xpm");
		i = 0;
	}
	else if (texture(data, "metro"))
	{
		load_img(data, &tmp, "tloading_screen/metro.xpm");
		data->map->c_rgb = -13;
		data->map->d_t = ft_strdup("textures/metrodoors.xpm");
		i = 0;
	}
	else if (texture(data, "walid"))
	{
		load_img(data, &tmp, "tloading_screen/walid_screen.xpm");
		data->map->c_rgb = -14;
		data->map->f_rgb = -10;
		i = 0;
	}
	loading_screen2(data, &tmp, i);
}
