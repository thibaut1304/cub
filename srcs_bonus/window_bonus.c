/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:32:34 by thhusser          #+#    #+#             */
/*   Updated: 2022/04/13 15:55:57 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_win(t_win *win)
{
	win->mlx_p = NULL;
	win->win_p = NULL;
	win->wid = 800;
	win->hei = 800;
}

void	free_win(t_global *cub)
{
	if (cub->win.mlx_p)
	{
		if (cub->win.win_p)
			mlx_destroy_window(cub->win.mlx_p, cub->win.win_p);
		mlx_destroy_display(cub->win.mlx_p);
		free(cub->win.mlx_p);
	}
	cub->win.mlx_p = NULL;
}

void	load_win(t_win *win)
{
	win->win_p = mlx_new_window(win->mlx_p, win->wid, win->hei, "Cub3D");
}
