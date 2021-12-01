
#include "../includes/cub.h"

void	init_grid(t_global *cub)
{
	cub->data.rows = 0;
	cub->data.cols = 0;
	cub->data.ceil = -1;
	cub->data.floor = -1;
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
		free(cub->tab[i]);
		cub->tab[i] = NULL;
	}
	free(cub->tab);
}
