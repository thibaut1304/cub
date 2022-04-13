/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preli_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:36:06 by thhusser          #+#    #+#             */
/*   Updated: 2022/04/13 15:54:34 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	check_open_texture_norm(t_global *g)
{
	if (g->map_textures.north_texture_path)
		check_open_texture(g->map_textures.north_texture_path, g);
	if (g->map_textures.south_texture_path)
		check_open_texture(g->map_textures.south_texture_path, g);
	if (g->map_textures.west_texture_path)
		check_open_texture(g->map_textures.west_texture_path, g);
	if (g->map_textures.east_texture_path)
		check_open_texture(g->map_textures.east_texture_path, g);
}

void	preliminaire(t_global *g)
{
	if (g->map_textures.sprite_texture_path == NULL)
		g->nb_texture = TEXT - 1;
	else
		g->nb_texture = TEXT;
	check_open_texture_norm(g);
	if (g->nb_texture == TEXT)
		check_open_texture(g->map_textures.sprite_texture_path, g);
	if (g->error)
	{
		print_error(g->error);
		return ;
	}
	g->win.mlx_p = mlx_init();
	if (!g->win.mlx_p)
	{
		record_error(g, "Couldn't init MLX\n");
		return ;
	}
	load_texture(g);
	if (g->error)
	{
		print_error(g->error);
		return ;
	}
}
