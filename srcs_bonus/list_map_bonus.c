/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 05:40:15 by thhusser          #+#    #+#             */
/*   Updated: 2022/04/13 15:55:00 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	count_grid(t_global *g, t_list *grid)
{
	int	column;
	int	rows;

	column = count_cols(grid);
	rows = ft_lstsize(grid);
	if (!column || !rows)
	{
		append_error(g, "", "Map has 0 columns or 0 rows\n");
		return (0);
	}
	g->tab = (char **)malloc(sizeof(char *) * rows + 1);
	if (!g->tab)
	{
		append_error(g, "", "Not enough memory to malloc the map\n");
		return (0);
	}
	g->number_columns = column;
	g->number_rows = rows;
	g->data.cols = g->number_columns;
	g->data.rows = g->number_rows;
	convert_grid(g, grid);
	return (1);
}

void	convert_grid(t_global *g, t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		g->tab[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	ft_lstclear(&list, &ft_del_list);
}

int	count_cols(t_list *grid)
{
	int	max;
	int	i;

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
