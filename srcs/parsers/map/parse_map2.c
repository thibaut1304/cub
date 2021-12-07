/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:05:16 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/07 13:35:29 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

char	*add_spaces(char *str, int largest_line)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char *) * largest_line + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	while (i < largest_line)
	{
		res[i] = ' ';
		i++;
	}
	res[i] = '\0';
	free(str);
	return (res);
}

void	process_map(t_global *g)
{
	int	i;

	i = -1;
	while (++i < g->number_rows)
		g->tab[i] = add_spaces(g->tab[i], g->number_columns);
	if (check_borders(g, g->number_rows, g->number_columns)
		|| check_walls(g, g->number_rows, g->number_columns))
		append_error(g, "", "Invalid map - wall missing\n");
}

int	check_end_file(int fd, int res)
{
	char	*line;

	line = NULL;
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		if (*line != '\0' || *line == '\t' || *line == 32)
		{
			free(line);
			line = NULL;
			return (1);
		}
		free(line);
		line = NULL;
	}
	return (0);
}
