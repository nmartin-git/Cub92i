/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:55:19 by nmartin           #+#    #+#             */
/*   Updated: 2025/06/02 14:58:19 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

typedef struct s_data
{
	void	*display;
	void	*window;
	void	*image;
	char	*adress;
	int		bpp;
	int		l_len;
	int		x;
	int		y;
}	t_data;

#endif