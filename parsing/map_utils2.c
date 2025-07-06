/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:47:47 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/06 19:04:48 by igrousso         ###   ########.fr       */
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
	else if (c == 'I')
		return (6);
	else if (c == 'A')
		return (7);
	else if (c == 'M')
		return (10);
	else if (c == 'F')
		return (11);
	else if (c == 'C')
		return (12);
	return (ft_putstr_fd("Error\nInvalid character\n", 2), -2);
}
