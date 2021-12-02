/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:31:38 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/02 17:00:17 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_player(t_player *player)
{
	player->pos.x = -1;
	player->pos.y = -1;
	player->turn_d = 0;
	player->walk_d = 0;
	player->lateral_d = 0;
	player->rot_ang = 0;
	player->mov_speed = 0.2;
	player->rot_speed = 3 * (M_PI / 180);
}

void	update(t_global *cub, t_player *player)
{
	float mov_step;
	float lateral_ang;
	float new_x;
	float new_y;

	player->rot_ang += player->turn_d * player->rot_speed;
	player->rot_ang = normalize(player->rot_ang);
	mov_step = player->walk_d * player->mov_speed;
	new_x = player->pos.x + cos(player->rot_ang) * mov_step;
	new_y = player->pos.y + sin(player->rot_ang) * mov_step;
	if (player->lateral_d != 0)
	{
		lateral_ang = player->rot_ang + ((M_PI / 2) * player->lateral_d);
		new_x = player->pos.x + cos(lateral_ang) * player->mov_speed;
		new_y = player->pos.y + sin(lateral_ang) * player->mov_speed;
	}
	if (!grid_is_wall(new_x, new_y, cub))
	{
		cub->player.pos.x = new_x;
		cub->player.pos.y = new_y;
	}
}
