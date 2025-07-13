/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:25:45 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/13 03:10:13 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	left_step(t_data *data, __uint64_t step)
{
    float   angle;
    float   x;
    float   y;

    angle = data->minimap->p_angle - (PI / 2);
    x = cos(angle);
    y = sin(angle);
    if (x < 0)
        go_left(data, fabs(x) * step);
    else
        go_right(data, fabs(x) * step);
    if (y < 0)
        go_up(data, fabs(y) * step);
    else
        go_down(data, fabs(y) * step);
}

void	right_step(t_data *data, __uint64_t step)
{
    float   angle;
    float   x;
    float   y;

    angle = data->minimap->p_angle + (PI / 2);
    x = cos(angle);
    y = sin(angle);
    if (x < 0)
        go_left(data, fabs(x) * step);
    else
        go_right(data, fabs(x) * step);
    if (y < 0)
        go_up(data, fabs(y) * step);
    else
        go_down(data, fabs(y) * step);
}

void	forward_step(t_data *data, __uint64_t step)
{
    float   angle;
    float   x;
    float   y;

    angle = data->minimap->p_angle;
    x = cos(angle);
    y = sin(angle);
    if (x < 0)
        go_left(data, fabs(x) * step);
    else
        go_right(data, fabs(x) * step);
    if (y < 0)
        go_up(data, fabs(y) * step);
    else
        go_down(data, fabs(y) * step);
}

void	backward_step(t_data *data, __uint64_t step)
{
    float   angle;
    float   x;
    float   y;

    angle = data->minimap->p_angle - PI;
    x = cos(angle);
    y = sin(angle);
    if (x < 0)
        go_left(data, fabs(x) * step);
    else
        go_right(data, fabs(x) * step);
    if (y < 0)
        go_up(data, fabs(y) * step);
    else
        go_down(data, fabs(y) * step);
}
