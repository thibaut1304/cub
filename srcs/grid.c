
#include "../includes/cub.h"

void	init_grid(t_global *cub)
{
	cub->data.rows = 0;
	cub->data.cols = 0;
	cub->data.ceil = 0;
	cub->data.floor = 0;
	cub->data.grid_flag = 0;
	cub->data.res = 0;
	cub->data.dist_pplane = 0.0;
	cub->data.num_sprt = 0;
}

void	free_grid(t_global *cub)
{
	int i;

	i = -1;
	while (++i < cub->data.rows)
	{
		free(cub->map[i]);
		cub->map[i] = NULL;
	}
	free(cub->map);
}

/*
** Duplicate the content of my list in my cub structure.
*/

int		fill_grid(t_global *cub, t_list *list)
{
	int i;

	i = 0;
	while (list)
	{
		cub->map[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	return (1);
}

/*
** Find number of rows and cols of the map. Malloc the required space to save
** the map parameter then fill it in my cub structure.
*/

int		grid_alloc(t_global *cub, t_list *list)
{
	int cols;
	int rows;

	cols = count_cols(list);
	rows = ft_lstsize(list);
	if (!cols || !rows)
		return (is_error("Map has 0 cols or 0 rows"));
	cub->map = malloc(sizeof(char *) * rows + 1);
	cub->data.cols = cols;
	cub->data.rows = rows;
	if (!cub->map)
		return (is_error("Not enough memory to malloc the map"));
	fill_grid(cub, list);
	return (1);
}

/*
** Malloc and fill my map. Then check if it's a valid map.
*/

int		grid_parsing(t_global *cub, t_list *list)
{
	if (!grid_alloc(cub, list))
	{
		ft_lstclear(&list, &ft_del_list);
		return (0);
	}
	ft_lstclear(&list, &ft_del_list);
	if (!check_player(cub) || !check_grid(cub) || !check_sprt(cub))
		return (0);
	return (1);
}
