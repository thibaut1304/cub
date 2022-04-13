/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:31:43 by yyuan             #+#    #+#             */
/*   Updated: 2022/04/13 15:55:18 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_elem(t_global *cub, int pxl_x, int pxl_y)
{
	double	x;
	double	y;

	x = cub->player.pos.x - (double)(DIST_PER_PIXEL * (CENTER_X - pxl_x));
	y = cub->player.pos.y - (double)(DIST_PER_PIXEL * (CENTER_Y - pxl_y));
	if (x > 0.0 && y > 0.0 && x < cub->number_columns && y < cub->number_rows)
	{
		if (cub->tab[(int)y][(int)x] == '1')
			my_mlx_pixel_put(&cub->win, pxl_x, pxl_y, 0xFFFFFF);
		else
			my_mlx_pixel_put(&cub->win, pxl_x, pxl_y, 0x191970);
	}
	else
		my_mlx_pixel_put(&cub->win, pxl_x, pxl_y, 0x191970);
}

void	draw_player(t_global *cub)
{
	t_pos	center;

	center = init_pos(MINIMAP_W / 2, MINIMAP_H / 2);
	square(center, 4, cub, 0xFF0000);
}

void	render_2d(t_global *cub)
{
	int	pxl_x;
	int	pxl_y;

	pxl_x = 0;
	if (cub->win.wid < 300 || cub->win.hei < 300)
		return ;
	while (pxl_x < MINIMAP_W)
	{
		pxl_y = 0;
		while (pxl_y < MINIMAP_H)
		{
			draw_elem(cub, pxl_x, pxl_y);
			pxl_y++;
		}
		pxl_x++;
	}
	draw_player(cub);
}
