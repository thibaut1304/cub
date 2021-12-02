/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:32:22 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/02 16:32:25 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	is_visible(t_global *cub, int i)
{
	float angle;

	angle = cub->sprt[i].ang;
	if (angle > M_PI)
		angle -= M_PI * 2;
	if (angle < -M_PI)
		angle += M_PI * 2;
	angle = abs((int)angle);
	if (angle < (FOV / 2))
		cub->sprt[i].visibility = 1;
	else
		cub->sprt[i].visibility = 0;
}

float	find_angle(t_global *cub, int i)
{
	float	delta_x;
	float	delta_y;
	float	ang;

	delta_x = cub->sprt[i].pos.x - cub->player.pos.x;
	delta_y = cub->sprt[i].pos.y - cub->player.pos.y;
	ang = atan2(delta_y, delta_x) - cub->player.rot_ang;
	return (ang);
}

void	sort_sprt(t_global *cub)
{
	t_sprt		tmp;
	int			i;
	int			j;

	i = -1;
	while (++i < cub->data.num_sprt - 1)
	{
		j = i + 1;
		if (cub->sprt[i].dist < cub->sprt[j].dist)
		{
			tmp = cub->sprt[i];
			cub->sprt[i] = cub->sprt[j];
			cub->sprt[j] = tmp;
		}
	}
}
