/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:31:02 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/02 16:31:05 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
