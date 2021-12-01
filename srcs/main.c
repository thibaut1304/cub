
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

void	init_cub(t_global *cub, char *map)
{
	(void)map;
	// t_list *list;

	// list = NULL;
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
	init_grid(cub);
	load_cub(cub, map);
}

/*
** Free all of our ressources.
*/

int		end_cub(t_global *cub)
{
	// print_param(cub);
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

static void 	preliminaire(t_global *g)
{
	printf(_BLUE"HERE\n"_NC);
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
	// g->window.mlx_ptr = mlx_init();
	// if (!cub->win.mlx_p)
		// return (is_error("Couldn't init MLX"));
	load_texture(g);
	if (g->error)
	{
		print_error(g->error);
		return ;
	}
}

static void		convert_input(t_global *cub)
{
	cub->data.cols = cub->number_columns;
	cub->data.rows = cub->number_rows;
}

void	load_cub(t_global *cub, char *file)
{
	t_list	*list;

	list = NULL;
	parse_input(cub, file, &list);
	convert_input(cub);
	if (cub->error)
	{
		// show_errors(&g);
		print_error(cub->error);
		// printf(_RED "Nombre d'erreurs : %d\n" _NC, g.nb_error);
		ft_lstclear(&list, &ft_del_list);
		end_cub(cub);
	}
	else 
	{
		// if (cub->data.txtr_err == 1 || cub->win.wid < 1)
		// {
		// 	// if (cub->win.wid < 1)
		// 		// is_error("Map has no valid resolution");
		// 	ft_lstclear(&list, &ft_del_list);
		// 	end_cub(cub);
		// }
		preliminaire(cub);
		if (cub->error || !load_sprt(cub))
				// !check_missing(cub))
			end_cub(cub);
		printf("Cub3d is launching..\n");
		run_cub(cub);
	}
}

/*
** If save arg true, then just copy the 1st image. Otherwise, loop the render.
*/

void	run_cub(t_global *cub)
{
	load_img(&cub->win);
	load_win(&cub->win);
    free_old_texture(cub, cub->nb_texture);
	mlx_hook(cub->win.win_p, 3, 1L << 1, key_released, &cub->player);
	mlx_hook(cub->win.win_p, 2, 1L << 0, key_pressed, cub);
	mlx_loop_hook(cub->win.mlx_p, render, cub);
	mlx_hook(cub->win.win_p, 33, 1L << 17, &end_cub, cub);
	mlx_loop(cub->win.mlx_p);
}


//checker les textures convert les datas

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
		ft_putstr("Error\nBad numbers of arguments\n");
	return (0);
}
