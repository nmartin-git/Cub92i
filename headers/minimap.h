/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:23:42 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/05 16:08:42 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# define MINIMAP_SIZE 1000
# define WALL 1
# define FLOOR 0
# define EMPTY 8

typedef struct s_minimap
{
	void	*display;
	void	*image;
	char	*adress;
	int		bpp;
	int		l_len;
	int		squareSize;
	int		p_color;
	int		w_color;
	int		f_color;
	int		b_color;
	int		x;
	int		y;
}	t_minimap;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

void	setMinimapColor(t_minimap *minimap);
int		getMinimapColor(t_minimap *minimap, int content);
void	minimapData(t_minimap *minimap, void *display, int x, int y);
void	pixelPutSquare(t_minimap *minimap, t_pos pixel, int color);
void	minimapCreate(t_minimap *minimap, int **map);

#endif