/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 05:40:15 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/01 16:20:09 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		count_grid(t_global *g, t_list *grid)
{
	int column;
	int rows;

	column = count_cols(grid);
	rows = ft_lstsize(grid);
	if (!column || !rows)
	{
		append_error(g, "", "Map has 0 columns or 0 rows\n");
		return (0);
	}
	// g->tab = NULL;
	g->tab = (char **)malloc(sizeof(char *) * rows + 1);
	// g->tab[rows] = NULL;
	g->number_columns = column;
	g->number_rows = rows;
	if (!g->tab)
	{
		append_error(g, "", "Not enough memory to malloc the map\n");
		return (0);
	}
	convert_grid(g, grid);
	return (1);
}

void 	del_list(void *grid)
{
	free(grid);
	grid = NULL;
}

void	convert_grid(t_global *g, t_list *list)
{
	int i;

	i = 0;
	while (list)
	{
		g->tab[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	ft_lstclear(&list, &del_list);
}

int		count_cols(t_list *grid)
{
	int max;
	int i;

	max = 0;
	while (grid)
	{
		i = ft_strlen(grid->content);
		if (i > max)
			max = i;
		grid = grid->next;
	}
	return (max);
}