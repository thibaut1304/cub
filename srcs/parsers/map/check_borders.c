/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:05:53 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/06 16:37:41 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

static int	check_top_and_bottom(char **map, int line_count)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	while (map[0][++i])
		if (map[0][i] != ' ' && map[0][i] != '1')
			flag += 1;
	i = -1;
	while (map[line_count - 1][++i])
		if (map[line_count - 1][i] != ' ' && map[line_count - 1][i] != '1')
			flag += 1;
	return (flag);
}

static int	check_left_and_right(char **map, int largest_line, t_global *g)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = -1;
	while (++i < g->number_rows)
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			flag += 1;
	}
	i = -1;
	while (++i < g->number_rows)
	{
		j = largest_line - 1;
		while (map[i][j] == ' ')
			j--;
		if (map[i][j] != '1')
			flag += 1;
	}
	return (flag);
}

static int	check_neight(char **map, int x, int y)
{
	if (is_in_charset(map[x + 1][y], "1NSEW0") && is_in_charset(map[x - 1][y], "1NSEW0") && is_in_charset(map[x][y - 1], "1NSEW0") && is_in_charset(map[x][y + 1], "1NSEW0"))
		return (0);
	return (1);
}

static int	check_zero_map(char **map, t_global *g)
{
	int	i;
	int	y;

	i = -1;
	while (++i < g->number_rows)
	{
		y = -1;
		while (++y < g->number_columns)
		{
			if (is_in_charset(map[i][y], "0NSEW"))
			{
				if (i == 0 || y == 0 || i == g->number_rows - 1
					|| y == g->number_columns - 1 || check_neight(map, i, y))
					return (1);
			}
		}
	}
	return (0);
}

int	check_borders(t_global *g, int line_count, int largest_line)
{
	int		flag;
	char	**map;

	flag = 0;
	map = g->tab;
	flag += check_top_and_bottom(map, line_count);
	flag += check_left_and_right(map, largest_line, g);
	flag += check_zero_map(map, g);
	return (flag);
}
