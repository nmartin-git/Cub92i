/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:47:47 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/04 17:56:42 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

/*
suite de ctoi
*/

int	ctoi2(char c)
{
	if (c == ' ' || c == '\n')
		return (8);
	else if (c == 'E')
		return (6);
	else if (c == 'F')
		return (7);
	return (ft_putstr_fd("Error\nInvalid character\n", 2), -2);
}
