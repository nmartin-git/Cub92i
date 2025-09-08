/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:40:01 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/09 00:27:48 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	pv_bar(t_data *data)
{
	int		x;
	int		y;

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

#include "time.h"

void    loading_screen(t_data *data)
{
    int i;
    t_image tmp;
    
    srand(time(0));
    i = (rand() % 6) + 1;
    if (i == 1)
        tmp.image = mlx_xpm_file_to_image(data->display, "tloading_screen/1.xpm", &tmp.tab_x, &tmp.tab_y);
    if (i == 2)
        tmp.image = mlx_xpm_file_to_image(data->display, "tloading_screen/2.xpm", &tmp.tab_x, &tmp.tab_y);
    if (i == 3)
        tmp.image = mlx_xpm_file_to_image(data->display, "tloading_screen/3.xpm", &tmp.tab_x, &tmp.tab_y);
    if (i == 4)
        tmp.image = mlx_xpm_file_to_image(data->display, "tloading_screen/4.xpm", &tmp.tab_x, &tmp.tab_y);
    if (i == 5)
        tmp.image = mlx_xpm_file_to_image(data->display, "tloading_screen/5.xpm", &tmp.tab_x, &tmp.tab_y);
    if (i == 6)
        tmp.image = mlx_xpm_file_to_image(data->display, "tloading_screen/golem.xpm", &tmp.tab_x, &tmp.tab_y);
    if (!tmp.image)
        cub_exit(1, "loading screen failed to load", data);
    // tmp.adress = mlx_get_data_addr(tmp.image, &tmp.bpp, &tmp.l_len, &i);
    mlx_put_image_to_window(data->display, data->window, tmp.image, (TAB_X - tmp.tab_x) / 2, (TAB_Y -  tmp.tab_y) / 2);
    mlx_destroy_image(data->display, tmp.image);
}
