/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:31:17 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/07 10:45:17 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	key_pressed(int key, t_global *cub)
{
	if (key == KEY_UP || key == KEY_W)
		cub->player.walk_d = 1;
	if (key == KEY_S || key == KEY_DOWN)
		cub->player.walk_d = -1;
	else if (key == KEY_LEFT)
		cub->player.turn_d = -1;
	else if (key == KEY_RIGHT)
		cub->player.turn_d = 1;
	else if (key == KEY_A)
		cub->player.lateral_d = -1;
	else if (key == KEY_D)
		cub->player.lateral_d = 1;
	else if (key == KEY_ESC)
		end_cub(cub);
	return (0);
}

int	key_released(int key, t_player *player)
{	
	if (key == KEY_S || key == KEY_UP
		|| key == KEY_DOWN || key == KEY_W)
		player->walk_d = 0;
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		player->turn_d = 0;
	else if (key == KEY_D || key == KEY_A)
		player->lateral_d = 0;
	return (0);
}
