/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_hz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:30:33 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/03 14:24:18 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_dcast	fill_hz_data(t_global *cub, t_ray *ray)
{
	t_dcast	hz_data;

	hz_data.found_wall = 0;
	hz_data.hit_x = 0;
	hz_data.hit_y = 0;
	hz_data.yinter = floor(cub->player.pos.y);
	if (ray->is_down)
		hz_data.yinter += 1;
	hz_data.xinter = cub->player.pos.x + (hz_data.yinter
			- cub->player.pos.y) / tan(ray->ray_ang);
	hz_data.ystep = 1;
	if (ray->is_up)
		hz_data.ystep *= -1;
	hz_data.xstep = 1 / tan(ray->ray_ang);
	if (ray->is_left && hz_data.xstep > 0)
		hz_data.xstep *= -1;
	if (ray->is_right && hz_data.xstep < 0)
		hz_data.xstep *= -1;
	hz_data.next_x = hz_data.xinter;
	hz_data.next_y = hz_data.yinter;
	return (hz_data);
}

void	hz_cast(t_ray *ray, t_global *cub, int i)
{
	t_dcast	hz_data;

	hz_data = fill_hz_data(cub, ray);
	if (ray->is_up)
		i = 1;
	while (hz_data.next_x >= 0 && hz_data.next_x <= cub->win.wid
		&& hz_data.next_y >= 0 && hz_data.next_y <= cub->win.hei)
	{
		if (grid_is_wall(hz_data.next_x, hz_data.next_y - i, cub))
		{
			hz_data.hit_y = hz_data.next_y;
			hz_data.hit_x = hz_data.next_x;
			hz_data.found_wall = 1;
			break ;
		}
		else
		{
			hz_data.next_x += hz_data.xstep;
			hz_data.next_y += hz_data.ystep;
		}
	}
	ray->hz_hit.x = hz_data.hit_x;
	ray->hz_hit.y = hz_data.hit_y;
	ray->found_hz_wall = hz_data.found_wall;
}
