
#include "../includes/cub.h"

/*
** Init all of our ressources and then start the game.
*/

void	print_param(t_global *g)
{
	printf("%f\n", g->data.dist_pplane);
	printf("%d\n", g->data.grid_flag);
	printf("%d\n", g->data.txtr_err);
	printf("%d\n", g->data.num_sprt);
	printf("%d\n", g->data.floor);
	printf("%d\n", g->data.ceil);
	printf("%d\n", g->data.cols);
	printf("%d\n", g->data.rows);
	printf("%d\n", g->data.res);
}

void	init_cub(t_global *cub, char *map)
{
	// (void)map;
	// t_list *list;

	// list = NULL;
	init_win(&cub->win);
	init_img(&cub->win.img);
	init_grid(cub);
	init_player(&cub->player);
	init_texture(cub);
	cub->ray_load = 0;
	cub->sprt_load = 0;
	cub->mlx_load = 0;
	cub->data.txtr_err = 0;
	// print_param(cub);
	load_cub(cub, map);
}

/*
** Free all of our ressources.
*/

int		end_cub(t_global *cub)
{
	free_texture(cub);
	if (cub->sprt_load == 1)
		free_sprt(cub);
	if (cub->ray_load == 1)
		free(cub->rays);
	if (cub->data.rows)
		free_grid(cub);
	if (cub->win.img.img)
		free_img(cub);
	free_win(cub);
	exit(0);
}

/*
** If we have a valid map, load the game.
*/

void	load_cub(t_global *cub, char *map)
{
	t_list	*list;

	list = NULL;
	if (parsing(cub, map, &list))
	{
		if (cub->data.txtr_err == 1 || cub->win.wid < 1)
		{
			if (cub->win.wid < 1)
				is_error("Map has no valid resolution");
			ft_lstclear(&list, &ft_del_list);
			end_cub(cub);
		}
		if (!grid_parsing(cub, list) || !load_texture(cub) || !load_sprt(cub) ||
				!check_missing(cub))
			end_cub(cub);
		printf("Cub3d is launching..\n");
		run_cub(cub);
	}
	else
	{
		ft_lstclear(&list, &ft_del_list);
		end_cub(cub);
	}
}

/*
** If save arg true, then just copy the 1st image. Otherwise, loop the render.
*/

void	run_cub(t_global *cub)
{
	load_img(&cub->win);
	load_win(&cub->win);
	mlx_hook(cub->win.win_p, 3, 1L << 1, key_released, &cub->player);
	mlx_hook(cub->win.win_p, 2, 1L << 0, key_pressed, cub);
	mlx_loop_hook(cub->win.mlx_p, render, cub);
	mlx_hook(cub->win.win_p, 33, 1L << 17, &end_cub, cub);
	mlx_loop(cub->win.mlx_p);
}

int		main(int ac, char **av)
{
	t_global cub;

	if (ac == 2)
	{
		if (cub_ext(av[1]))
			init_cub(&cub, av[1]);
		return (0);
	}
	else
		return (is_error("Wrong numbers of arguments"));
	return (0);
}
