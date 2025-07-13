/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:48:43 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/13 02:53:47 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CROSSHAIR_H
# define CROSSHAIR_H

# include "game.h"
# include "struct_utils.h"

# define WIDTH_C 2
# define LENGHT_C 6
# define GAP_C 6
# define IMG_SIZE ((LENGHT_C * 2) + GAP_C + 2)

# define POS_C_X (TAB_X / 2 - (IMG_SIZE) / 2)
# define POS_C_Y (TAB_Y / 2 - (IMG_SIZE) / 2)

# define GREEN 65280
# define RED 16711680
# define CYAN 65535
# define BLUE 255
# define YELLOW 16776960
# define BURGUNDY 8388640
# define WHITE 16777215
# define VIOLET 8388808

void	vertical_crosshair(t_image *crosshair, int color);
void	horizontal_crosshair(t_image *crosshair, int color);
int		init_crosshair(t_data *data);

#endif