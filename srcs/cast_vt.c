/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:30:48 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/03 14:28:22 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_dcast	fill_vt_data(t_global *cub, t_ray *ray)
{
	t_dcast	vt_data;

	vt_data.found_wall = 0;
	vt_data.hit_x = 0;
	vt_data.hit_y = 0;
	vt_data.xinter = floor(cub->player.pos.x);
	if (ray->is_right)
		vt_data.xinter += 1.0;
	vt_data.yinter = cub->player.pos.y + (vt_data.xinter
			- cub->player.pos.x) * tan(ray->ray_ang);
	vt_data.xstep = 1.0;
	if (ray->is_left)
		vt_data.xstep *= -1;
	vt_data.ystep = 1.0 * tan(ray->ray_ang);
	if (ray->is_up && vt_data.ystep > 0)
		vt_data.ystep *= -1;
	if (ray->is_down && vt_data.ystep < 0)
		vt_data.ystep *= -1;
	vt_data.next_x = vt_data.xinter;
	vt_data.next_y = vt_data.yinter;
	return (vt_data);
}

void	vt_cast(t_ray *ray, t_global *cub, int i)
{
	t_dcast	vt_data;

	vt_data = fill_vt_data(cub, ray);
	if (ray->is_left)
		i = 1;
	while (vt_data.next_x >= 0 && vt_data.next_x <= cub->win.wid
		&& vt_data.next_y >= 0 && vt_data.next_y <= cub->win.hei)
	{
		if (grid_is_wall(vt_data.next_x - i, vt_data.next_y, cub))
		{
			vt_data.hit_y = vt_data.next_y;
			vt_data.hit_x = vt_data.next_x;
			vt_data.found_wall = 1;
			break ;
		}
		else
		{
			vt_data.next_x += vt_data.xstep;
			vt_data.next_y += vt_data.ystep;
		}
	}
	ray->vt_hit.x = vt_data.hit_x;
	ray->vt_hit.y = vt_data.hit_y;
	ray->found_vt_wall = vt_data.found_wall;
}
