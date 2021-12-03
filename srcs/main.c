/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:31:31 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/03 11:38:18 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void 	ft_init_textures_map(t_map_textures *text)
{
	text->north_texture_path = NULL;
	text->south_texture_path = NULL;
	text->east_texture_path = NULL;
	text->west_texture_path = NULL;
	text->sprite_texture_path = NULL;
	text->floor_color = -1;
	text->ceiling_color = -1;
}

static void	init_cub(t_global *cub, char *map)
{
	init_win(&cub->win);
	init_img(&cub->win.img);
	init_grid(cub);
	init_player(&cub->player);
	ft_init_textures_map(&cub->map_textures);
	cub->error = NULL;
	cub->nb_texture = 0;
	cub->valid_parameter_count = 0;
	cub->new_line = 0;
	cub->in_map = 0;
	cub->ray_load = 0;
	cub->sprt_load = 0;
	cub->mlx_load = 0;
	cub->data.txtr_err = 0;
	cub->fd = 0;
	init_grid(cub);
	load_cub(cub, map);
}

int		end_cub(t_global *cub)
{
	free_texture(cub);
	if (cub->ray_load == 1)
		free(cub->rays);
	if (cub->data.rows)
		free_grid(cub);
	if (cub->win.img.img)
		free_img(cub);
	free_win(cub);
	ft_lstclear(&cub->error, &ft_del_list);
	ft_lstclear(&cub->list, &ft_del_list);
	exit(0);
}

static void 	preliminaire(t_global *g)
{
	if (g->map_textures.sprite_texture_path == NULL)
		g->nb_texture = TEXT - 1;
	else
		g->nb_texture = TEXT;
	check_open_texture(g->map_textures.north_texture_path, g);
	check_open_texture(g->map_textures.south_texture_path, g);
	check_open_texture(g->map_textures.west_texture_path, g);
	check_open_texture(g->map_textures.east_texture_path, g);
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

void	load_cub(t_global *cub, char *file)
{

	cub->list = NULL;
	parse_input(cub, file, &cub->list);
	if (cub->error)
	{
		print_error(cub->error);
		end_cub(cub);
	}
	else 
	{
		cub->data.dist_pplane = (cub->win.wid / 2) / tan(FOV / 2);
		cub->rays = malloc(sizeof(t_ray) * cub->win.wid);
		if (!cub->rays)
		{
			record_error(cub, "Not enough memory to malloc rays");
			return ;
		}
		cub->ray_load = 1;
		preliminaire(cub);
		if (cub->error)
			end_cub(cub);
		ft_putstr("Cub3d is launching..\n");
		run_cub(cub);
	}
}

void	run_cub(t_global *cub)
{
	load_img(&cub->win);
	load_win(&cub->win);
    free_old_texture(cub, cub->nb_texture);
	mlx_hook(cub->win.win_p, 2, 1L << 0, key_pressed, cub);
	mlx_hook(cub->win.win_p, 3, 1L << 1, key_released, &cub->player);
	mlx_loop_hook(cub->win.mlx_p, render, cub);
	mlx_hook(cub->win.win_p, 33, 1L << 17, &end_cub, cub);
	mlx_loop(cub->win.mlx_p);
}

static int     is_valid_file(char *file, char *str)
{
	int		i;

	i = 0;
	while (file[i] != '\0')
		i++;
	i -= 4;
	if (i > 0)
		return (ft_strequ(&file[i], str));
	else
		return (0);
}

int		main(int argc, char **argv)
{
	t_global cub;

	if (argc == 2)
	{
		if (is_valid_file(argv[1], ".cub"))
			init_cub(&cub, argv[1]);
		else
			ft_putstr("Is not a '.cub' file\n");
	}
	else
		ft_putstr("Error\nBad numbers of arguments\n");
	return (0);
}
