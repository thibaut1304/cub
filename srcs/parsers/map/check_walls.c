/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:00 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/06 16:03:00 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

static int	check_neighbour(char **map, int x, int y, char c)
{
	if (c == 'N')
		x--;
	if (c == 'S')
		x++;
	if (c == 'W')
		y--;
	if (c == 'E')
		y++;
	if (map[x][y] == ' ' || map[x][y] == '1')
		return (1);
	return (0);
}

static int	check_nswe(char **map, int x, int y, int row_count)
{
	int	flag;

	flag = 1;
	if (x == 0)
		if (check_neighbour(map, x, y, 'S'))
			if (check_neighbour(map, x, y, 'W'))
				if (check_neighbour(map, x, y, 'E'))
					flag = 0;
	if (x == row_count)
		if (check_neighbour(map, x, y, 'N'))
			if (check_neighbour(map, x, y, 'W'))
				if (check_neighbour(map, x, y, 'E'))
					flag = 0;
	if (x != 0 && x != row_count)
		if (check_neighbour(map, x, y, 'N'))
			if (check_neighbour(map, x, y, 'S'))
				if (check_neighbour(map, x, y, 'W'))
					if (check_neighbour(map, x, y, 'E'))
						flag = 0;
	return (flag);
}

int	check_walls(t_global *g, int row_count, int col_count)
{
	int		x;
	int		y;
	int		flag;
	char	**map;

	flag = 0;
	map = g->tab;
	x = -1;
	while (map[++x] && x < row_count - 1)
	{
		y = 0;
		while (map[x][++y]  && y < col_count - 1)
			if (map[x][y] == ' ')
				flag += check_nswe(map, x, y, row_count - 1);
	}
	return (flag);
}
