/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:31:38 by thhusser          #+#    #+#             */
/*   Updated: 2022/04/13 15:55:06 by thhusser         ###   ########.fr       */
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
	player->mov_speed = 0.1;
	player->rot_speed = 1.5 * (M_PI / 180);
}

/*printf("mouse get x: %d, y: %d. Turn: %c\n",
	x, y, win->wid / 2 - x < 0 ? 'R' : 'L');*/
int	mouse_move(const t_win *const win)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(win->mlx_p, win->win_p, &x, &y);
	mlx_mouse_move(win->mlx_p, win->win_p, win->wid / 2, win->hei / 2);
	if (x == win->wid / 2)
		return (0);
	if (win->wid / 2 - x < 0)
		return (1);
	else
		return (-1);
}

void	update(t_global *cub, t_player *player)
{
	float	mov_step;
	float	lateral_ang;
	float	new_x;
	float	new_y;

	if (player->turn_d == 0)
		player->turn_d = mouse_move(&cub->win);
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
	player->turn_d = 0;
}
