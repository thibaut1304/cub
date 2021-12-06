/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:31:31 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/06 19:29:31 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	end_cub(t_global *cub)
{
	free_texture(cub);
	free_old_texture(cub, TEXT);
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

static int	check_dir_map(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (fd >= 0)
		close(fd);
	fd = open(file, O_DIRECTORY);
	if (!(fd < 0))
		return (2);
	if (fd >= 0)
		close(fd);
	return (0);
}

int	main(int argc, char **argv)
{
	t_global	cub;

	if (argc == 2)
	{
		if (is_valid_file(argv[1], ".cub") && !check_dir_map(argv[1]))
			init_cub(&cub, argv[1]);
		else if (check_dir_map(argv[1]) == 2)
			ft_putstr("Error\nThe parameter is a directory\n");
		else if (check_dir_map(argv[1]) == 1)
			ft_putstr("Error\nWe can't open the map\n");
		else
			ft_putstr("Error\nIs not a '.cub' file\n");
	}
	else
		ft_putstr("Error\nBad numbers of arguments\n");
	return (0);
}
