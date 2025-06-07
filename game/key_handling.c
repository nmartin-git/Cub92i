/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:26:13 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/07 16:33:38 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	mooveCursor(t_data *data, int x, int y)
{
	data->minimap->cursor_x += x;
	data->minimap->cursor_y += y;
	mlx_put_image_to_window(data->display, data->window, data->minimap->cursor->image, data->minimap->cursor_x, data->minimap->cursor_y);
}
