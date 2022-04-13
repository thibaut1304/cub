/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:31:58 by thhusser          #+#    #+#             */
/*   Updated: 2022/04/13 15:55:49 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_ray(t_ray *ray, float ray_ang)
{
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->dist = 0;
	ray->was_vt_hit = 0;
	if (ray_ang > 0 && ray_ang < M_PI)
		ray->is_down = 1;
	else
		ray->is_down = 0;
	ray->is_up = !ray->is_down;
	if (ray_ang < 0.5 * M_PI || ray_ang > 1.5 * M_PI)
		ray->is_right = 1;
	else
		ray->is_right = 0;
	ray->is_left = !ray->is_right;
}

t_line	init_line(t_pos a, t_pos b)
{
	t_line	line;

	line.start.x = MINIMAP_SCALE * a.x;
	line.start.y = MINIMAP_SCALE * a.y;
	line.end.x = MINIMAP_SCALE * b.x;
	line.end.y = MINIMAP_SCALE * b.y;
	return (line);
}

t_pos	init_pos(float x, float y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

void	ft_init_textures_map(t_map_textures *text)
{
	text->north_texture_path = NULL;
	text->south_texture_path = NULL;
	text->east_texture_path = NULL;
	text->west_texture_path = NULL;
	text->sprite_texture_path = NULL;
	text->floor_color = -1;
	text->ceiling_color = -1;
}

void	init_cub(t_global *cub, char *map)
{
	init_win(&cub->win);
	init_img(&cub->win.img);
	init_grid(cub);
	init_player(&cub->player);
	ft_init_textures_map(&cub->map_textures);
	cub->error = NULL;
	cub->text = NULL;
	cub->tab = NULL;
	cub->nb_texture = 0;
	cub->valid_parameter_count = 0;
	cub->new_line = 0;
	cub->in_map = 0;
	cub->res = 1;
	cub->ray_load = 0;
	cub->sprt_load = 0;
	cub->mlx_load = 0;
	cub->data.txtr_err = 0;
	cub->fd = 0;
	init_grid(cub);
	load_cub(cub, map);
}
