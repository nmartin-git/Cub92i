/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:35:41 by igrousso          #+#    #+#             */
/*   Updated: 2025/09/17 15:26:37 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKGROUND_H
# define BACKGROUND_H

# include "struct_utils.h"

typedef struct s_image	t_image;

typedef struct s_tmp
{
	int					s_len;
	int					d_len;
	int					x;
	int					y;
}						t_tmp;

/* background_utils */

int						decode_r(int rgb);
int						decode_g(int rgb);
int						decode_b(int rgb);
void					init_image(t_image *img);
int						get_adress(t_data *data, t_image *new, t_image *new2);

/* blackground */

void					paint_ceiling(char *dst, t_data *data, int j);
void					paint_floor(char *dst, t_data *data, int j);
void					gateway_paint(char *dst, t_image *img, t_data *data,
							int i);
int						paint_floor_and_ceiling(t_image *img, t_data *data);

/* merge_img */

void					put_pixel_img(t_image *img, int x, int y, int color);
unsigned int			get_pixel_img(t_image *img, int x, int y);
void					put_img_to_img(t_image *dst, t_image *src, int x,
							int y);

/* easter eggs */

void					fill_command(char **command, char *str, char *xlen,
							char *ylen);
int						convert_xpm(char *str, int x, int y);
int						easter_egg_img(t_data *data, t_image *newimg,
							t_image *new2);
int						easter_egg(t_image *img, t_data *data);
int						easter_egg_img2(t_data *data, t_image *newimg,
							t_image *new2);

#endif