/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:20:44 by igrousso          #+#    #+#             */
/*   Updated: 2025/06/04 11:56:35 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_map
{
	int		**map;
	char	*n_t;
	char	*s_t;
	char	*e_t;
	char	*w_t;
	int		f_rgb;
	int		c_rgb;
	int		row;
	int		col;
}			t_map;

#endif