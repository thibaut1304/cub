/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:33 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/01 19:38:57 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static	void	fetch_arguments(char *line, t_global *g)
{
	int		i;
	int		arg_count;
	char	**line_split;

	i = -1;
	arg_count = 0;
	line_split = ft_split(line, ' ');
	arg_count = number_of_args(line_split);
	if (arg_count == 1)
		append_error(g, line_split[0], " : not enough arguments\n");
	if (arg_count > 3)
		append_error(g, line_split[0], " : too many arguments\n");
	if (arg_count == 2)
		parse_line_paths(line_split, g);
	if ((g->valid_parameter_count == 7  || g->valid_parameter_count == 6 ) && !g->in_map && !*line)
	{
		g->new_line = 1;
	}
	while (line_split[++i])
		free(line_split[i]);
	free(line_split);
}

static void		check_parameter_count_and_map(t_global *g)
{
	// printf("NUMBER ARG --> %d\n", g->valid_parameter_count);
	if ((g->valid_parameter_count != 7 && g->nb_texture == 5) || (g->valid_parameter_count != 6 && g->nb_texture == 4))
		append_error(g, "", "Not enough valid parameters\n");
	if (!g->new_line)
		append_error(g, "", "Not new line after parameters\n");
	else if (*(g->tab) == NULL)
		append_error(g, "", "No map found\n");
}

void			parse_input(t_global *g, char *file, t_list **list)
{
	int		fd;
	char	*line;
	int 	res;
	res = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		append_error(g, "", "Cannot open map\n");
		return ;
	}
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		if (detect_map_line(line) && res != 0)
		{
			g->in_map = 1;
			parse_map(line, fd, g, list);
			break ;
		}
		fetch_arguments(line, g);
		free(line);
		line = NULL;
	}
	check_parameter_count_and_map(g);
	free(line);
	line = NULL;
	close(fd);
}
