
#include "../includes/cub.h"

void	init_player(t_player *player)
{
	player->pos.x = -1;
	player->pos.y = -1;
	player->turn_d = 0;
	player->walk_d = 0;
	player->lateral_d = 0;
	player->rot_ang = 0;
	player->mov_speed = 0.3;
	player->rot_speed = 2 * (M_PI / 180);
}

/*
** After each movement. Determine the new position of our player.
** Knowing our player rotation angle and lenght of his step. We can find x & y
** with cos and sin.
*/

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

/*
** Save player pos & orientation in our structure
*/

