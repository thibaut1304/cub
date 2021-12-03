/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:58:56 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/03 14:30:06 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	key_space(int key, t_global *cub)
{
	static int	val = 0;

	if (key == 32)
	{
		if (val == 0)
		{
			mlx_do_key_autorepeatoff(cub->win.mlx_p);
			val = 1;
		}
		else if (val == 1)
		{
			mlx_do_key_autorepeaton(cub->win.mlx_p);
			val = 0;
		}
		return (1);
	}
	return (0);
}

int	key_pressed(int key, t_global *cub)
{
	if (key_space(key, cub))
		return (0);
	else if (key == KEY_Z || key == KEY_UP || key == KEY_W)
		cub->player.walk_d = 1;
	else if (key == KEY_S || key == KEY_DOWN)
		cub->player.walk_d = -1;
	else if (key == KEY_LEFT)
		cub->player.turn_d = -1;
	else if (key == KEY_RIGHT)
		cub->player.turn_d = 1;
	else if (key == KEY_Q || key == KEY_A)
		cub->player.lateral_d = -1;
	else if (key == KEY_D)
		cub->player.lateral_d = 1;
	else if (key == KEY_ESC)
		end_cub(cub);
	update(cub, &cub->player);
	render(cub);
	return (0);
}

int	key_released(int key, t_player *player)
{	
	if (key == KEY_Z || key == KEY_S || key == KEY_UP
		|| key == KEY_DOWN || key == KEY_W)
		player->walk_d = 0;
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		player->turn_d = 0;
	else if (key == KEY_Q || key == KEY_D || key == KEY_A)
		player->lateral_d = 0;
	return (0);
}
