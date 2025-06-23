/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:35:41 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/14 15:01:45 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKGROUND_H
# define BACKGROUND_H

# include "struct_utils.h"

/* background_utils */

int				decode_r(int rgb);
int				decode_g(int rgb);
int				decode_b(int rgb);
void			init_image(t_image *img);

/* blackground */

void			paint_ceiling(char *dst, t_data *data, int j);
void			paint_floor(char *dst, t_data *data, int j);
void			gateway_paint(char *dst, t_image *img, t_data *data, int i);
int				paint_floor_and_ceiling(t_image *img, t_data *data);

/* merge_img */

void			put_pixel_img(t_image *img, int x, int y, int color);
unsigned int	get_pixel_img(t_image *img, int x, int y);
void			put_img_to_img(t_image *dst, t_image *src, int x, int y);

#endif