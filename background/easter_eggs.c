/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easter_eggs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:44:50 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/12 14:42:46 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/background.h"
#include "../headers/game.h"

/*
va remplir la string command pour l'execution
*/

void	fill_command(char **command, char *str, char *xlen, char *ylen)
{
	int	len;

	len = 21 + strlen(xlen) + strlen(ylen) + (strlen(str) * 2);
	ft_strlcat((*command), "convert ", len);
	ft_strlcat((*command), str, len);
	ft_strlcat((*command), " -resize ", len);
	ft_strlcat((*command), xlen, len);
	ft_strlcat((*command), "x", len);
	ft_strlcat((*command), ylen, len);
	ft_strlcat((*command), "! ", len);
	ft_strlcat((*command), str, len);
}

/*
change la resolution du fichier xpm en fonction de la taille
de la fenêtre
*/

int	convert_xpm(char *str)
{
	char	*command;
	int		len;
	char	*xlen;
	char	*ylen;

	xlen = ft_itoa(TAB_X);
	if (!xlen)
		return (write(2, "Error\nMalloc fail\n", 18));
	ylen = ft_itoa(TAB_Y / 2);
	if (!ylen)
		return (free(xlen), write(2, "Error\nMalloc fail\n", 18));
	len = 21 + strlen(xlen) + strlen(ylen) + (strlen(str) * 2);
	command = calloc(len, sizeof(char));
	if (!command)
		return (free(xlen), free(ylen), write(2, "Error\nMalloc fail\n", 18));
	fill_command(&command, str, xlen, ylen);
	free(xlen);
	free(ylen);
	if (system(command))
		return (free(command), write(2, "Error\nExec error\n", 17));
	free(command);
	return (0);
}

/*
ouvre le bon fichier xpm
*/

int	easter_egg_img(t_data *data, t_image *newimg)
{
	newimg = NULL;
	if (data->map->c_rgb == -10)
	{
		if (convert_xpm(".test.xpm"))
			return (1);
		// newimg->image = mlx_xpm_file_to_image(data->display, "./.ceiling.xpm", \
		// 	&newimg->w, &newimg->h);
	}
	else if (data->map->c_rgb == -11)
	{
		if (convert_xpm(".test2.xpm"))
			return (1);
		// newimg->image = mlx_xpm_file_to_image(data->display, "./.ceiling2.xpm", \
		// 	&newimg->w, &newimg->h);
	}
	else if (data->map->c_rgb == -12)
	{
		if (convert_xpm(".test.xpm"))
			return (1);
		// newimg->image = mlx_xpm_file_to_image(data->display, "./.ceiling3.xpm", \
		// 	&newimg->w, &newimg->h);
	}
	return (0);
}

/*
change la couleur du ciel
*/

int	easter_egg(t_image *img, t_data *data)
{
	t_image	new;
	int		null;

	init_image(&new);
	if (easter_egg_img(data, &new))
		return (1);
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
