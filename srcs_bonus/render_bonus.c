/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:31:43 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/03 14:41:01 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	render_floor(t_global *cub, t_ray rays, int i)
{
	int	j;

	j = rays.bot_px;
	while (j < cub->win.hei)
	{
		my_mlx_pixel_put(&cub->win, i, j, cub->data.floor);
		j++;
	}
}

void	render_ceil(t_global *cub, t_ray rays, int i)
{
	int	j;

	j = -1;
	while (++j < rays.top_px)
		my_mlx_pixel_put(&cub->win, i, j, cub->data.ceil);
}

void	render_wall(t_global *cub, int i, float wall_hei)
{
	float	text_x;
	float	text_y;
	int		color;
	int		j;

	if (cub->rays[i].was_vt_hit)
		text_x = fmod(cub->rays[i].wall_hit_y, 1)
			* cub->text[cub->rays[i].id].wid;
	else
		text_x = fmod(cub->rays[i].wall_hit_x, 1)
			* cub->text[cub->rays[i].id].wid;
	j = cub->rays[i].top_px - 1;
	while (++j < cub->rays[i].bot_px)
	{
		text_y = (j + (wall_hei / 2) - (cub->win.hei / 2))
			* ((float)cub->text[cub->rays[i].id].hei / wall_hei);
		color = grep_color(cub->text[cub->rays[i].id], text_x, text_y);
		my_mlx_pixel_put(&cub->win, i, j, color);
	}
}

void	render_3d(t_global *cub)
{
	float	wall_dist;
	float	wall_hei;
	int		top_px;
	int		bot_px;
	int		i;

	i = -1;
	while (++i < cub->win.wid)
	{
		wall_dist = cub->rays[i].dist * cos(cub->rays[i].ray_ang
				- cub->player.rot_ang);
		wall_hei = cub->data.dist_pplane / wall_dist;
		top_px = (cub->win.hei / 2) - (wall_hei / 2);
		bot_px = (cub->win.hei / 2) + (wall_hei / 2);
		if (top_px < 0)
			top_px = 0;
		if (bot_px > cub->win.hei)
			bot_px = cub->win.hei;
		cub->rays[i].top_px = top_px;
		cub->rays[i].bot_px = bot_px;
		render_ceil(cub, cub->rays[i], i);
		render_floor(cub, cub->rays[i], i);
		render_wall(cub, i, wall_hei);
	}
}

int	render(t_global *cub)
{
	cast_all_rays(cub);
	render_3d(cub);
	render_2d(cub);
	mlx_put_image_to_window(cub->win.mlx_p, cub->win.win_p,
		cub->win.img.img, 0, 0);
	return (1);
}
