/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:20:44 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/04 07:28:18 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_map
{
    int **map;
    char *N_t;
    char *S_t;
    char *E_t;
    char *W_t;
    int F_rgb;
    int C_rgb;
    int row;
    int col;
}   t_map;

#endif