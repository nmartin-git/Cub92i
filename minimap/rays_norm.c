/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:22:24 by nmartin           #+#    #+#             */
/*   Updated: 2025/09/17 17:05:15 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	raycast_norm(t_pos *ph, t_pos *pv, t_pos *origin, t_long *dst)
{
	if (ph->x == TAN_ERR || ph->y == TAN_ERR)
		dst->x = LONG_MAX;
	else
		dst->x = pow(ph->x - origin->x, 2) + pow(ph->y - origin->y, 2);
	if (pv->x == TAN_ERR || pv->y == TAN_ERR)
		dst->y = LONG_MAX;
	else
		dst->y = pow(pv->x - origin->x, 2) + pow(pv->y - origin->y, 2);
}

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	tan_err(t_pos *pos)
{
	pos->x = TAN_ERR;
	pos->y = TAN_ERR;
}

int	wall_norm_de_neuille(t_double *r, t_pos *pos, int wall_door)
{
	pos->x = (int)r->x;
	pos->y = (int)r->y;
	if (wall_door == C_DOOR)
		return (1);
	return (0);
}

void	wall_norm(t_double *r, t_double *off, int *depth_of_field)
{
	r->x += off->x;
	r->y += off->y;
	*depth_of_field += 1;
}