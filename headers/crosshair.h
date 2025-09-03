/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:48:43 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/13 18:37:55 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CROSSHAIR_H
# define CROSSHAIR_H

# include "game.h"
# include "struct_utils.h"

# define WIDTH_C 2
# define LENGHT_C 6
# define GAP_C 6

# define GREEN 65280
# define RED 16711680
# define CYAN 65535
# define BLUE 255
# define YELLOW 16776960
# define BURGUNDY 8388640
# define WHITE 16777215
# define VIOLET 8388808

typedef struct s_image	t_image;

typedef struct s_crosshair
{
	int					img_size;
	int					pos_c_x;
	int					pos_c_y;
	t_image				*cross_img;
}						t_crosshair;

void					vertical_crosshair(t_crosshair *crosshair, int color);
void					horizontal_crosshair(t_crosshair *crosshair, int color);
int						init_crosshair(t_data *data);
void					free_crosshair(t_data *data);

#endif