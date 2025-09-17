/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_pitie_norminette.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:10:46 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/17 18:11:14 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	off_norm(t_double *off, double x, double y, int *d)
{
	off->x = x;
	off->y = y;
	*d = 0;
}

void	gagner_4lignes(double angle, t_double *r, t_minimap *m, double *a)
{
	*a = -1 / tan(angle);
	if (angle > PI)
	{
		r->y = (((int)(m->cursor_y + m->pxl_size / 3 \
			- MINIMAP_SIZE / 15) / m->pxl_size) * m->pxl_size) \
			- 1 + MINIMAP_SIZE / 15;
		r->x = (m->cursor_y + m->pxl_size / 3 - r->y) * *a \
			+ m->cursor_x + m->pxl_size / 3;
	}
	else if (angle < PI && angle != 0)
	{
		r->y = (((int)(m->cursor_y + m->pxl_size / 3 \
			- MINIMAP_SIZE / 15) / m->pxl_size) * m->pxl_size) \
			+ m->pxl_size + MINIMAP_SIZE / 15;
		r->x = (m->cursor_y + m->pxl_size / 3 - r->y) \
			* *a + m->cursor_x + m->pxl_size / 3;
	}
}

void	gagner_5lignes(double a, t_double *r, t_minimap *m, double *n)
{
	*n = -tan(a);
	if (a > PI / 2 && a < 3 * PI / 2)
	{
		r->x = (((int)(m->cursor_x + m->pxl_size / 3 \
			- MINIMAP_SIZE / 15) / m->pxl_size) * m->pxl_size) \
			- 1 + MINIMAP_SIZE / 15;
		r->y = (m->cursor_x + m->pxl_size / 3 - r->x) * *n \
			+ m->cursor_y + m->pxl_size / 3;
	}
	else if ((a >= 0 && a < PI / 2) || (a > 3 * PI / 2 && a < 2 * PI))
	{
		r->x = (((int)(m->cursor_x + m->pxl_size / 3 \
			- MINIMAP_SIZE / 15) / m->pxl_size) * m->pxl_size) \
			+ m->pxl_size + MINIMAP_SIZE / 15;
		r->y = (m->cursor_x + m->pxl_size / 3 - r->x) * *n \
			+ m->cursor_y + m->pxl_size / 3;
	}
}

void	juste_pour_1ligne(t_pos *map, t_double *r, int pxl)
{
	map->x = (int)(r->x - MINIMAP_SIZE / 15) / pxl;
	map->y = (int)(r->y - MINIMAP_SIZE / 15) / pxl;
}
