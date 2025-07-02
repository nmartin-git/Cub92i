/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_no_leaks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:42:48 by igrousso          #+#    #+#             */
/*   Updated: 2025/07/02 18:45:28 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef HAS_XFIXES
# include "mlx_int.h"
# include <X11/extensions/Xfixes.h>
#else
# include "../minilibx-linux/mlx.h"
#endif

#ifdef HAS_XFIXES

void	mlx_mouse_hide_no_leak(void *mlx, void *win)
{
	t_xvar		*xvar;
	t_win_list	*xwin;

	if (mlx == NULL || win == NULL)
		return ;
	xvar = (t_xvar *)mlx;
	xwin = (t_win_list *)win;
	XFixesHideCursor(xvar->display, xwin->window);
}

void	mlx_mouse_show_no_leak(void *mlx, void *win)
{
	t_xvar		*xvar;
	t_win_list	*xwin;

	if (mlx == NULL || win == NULL)
		return ;
	xvar = (t_xvar *)mlx;
	xwin = (t_win_list *)win;
	XFixesShowCursor(xvar->display, xwin->window);
}

#else

void	mlx_mouse_hide_no_leak(void *mlx, void *win)
{
	if (!mlx || !win)
		return ;
	mlx_mouse_hide(mlx, win);
}

void	mlx_mouse_show_no_leak(void *mlx, void *win)
{
	if (!mlx || !win)
		return ;
	mlx_mouse_show(mlx, win);
}

#endif