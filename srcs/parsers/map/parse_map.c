/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:09 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/01 19:23:13 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

static char	*add_spaces(char *str, int largest_line)
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

static void	process_map(t_global *g)
{
	int		i;
	// int		largest_line;
	// int		line_count;
	// int		len;

	// i = 0;
	// len = 0;
	// largest_line = 0;
	// line_count = 0;
	// while (g->tab[i])
	// {
	// 	len = ft_strlen(g->tab[i]);
	// 	if (largest_line < len)
	// 		largest_line = len;
	// 	line_count++;
	// 	i++;
	// }
	// g->map->number_columns = largest_line;
	// g->map->number_rows = line_count;
	i = -1;
	while (++i < g->number_rows)
		g->tab[i] = add_spaces(g->tab[i], g->number_columns);
	if (check_borders(g, g->number_rows, g->number_columns) ||
	check_walls(g, g->number_rows, g->number_columns))
		append_error(g, "", "Invalid map - wall missing\n");
}

static void		recovery_map(t_global *g, char *line, t_list **list)
{
	t_list	*new_elem;

	g->in_map = 1;
	new_elem = ft_lstnew(ft_strdup(line));
	ft_lstadd_back(list, new_elem);
}

static void	fetch_map(t_global *g, char *line, int fd, t_list **list)
{
	int res;

	res = 1;
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		if (detect_map_line(line) == 0)
		{
			if (*line != '\0')
				append_error(g, "", "Invalid map, wrong data\n");
			free(line);
			line = NULL;
			break ;
		}

		// je tente de record la map en liste chainee
		// valide suprresion des leaks okay
		if (*line != 0)
			recovery_map(g, line, list);
		// g->tab = dual_realloc(g->tab, line);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd);
}

// static void	check_remaining_map_data(t_global *g, char *line, int fd)
// {
// 	while ((get_next_line(fd, &line) > 0))
// 	{
// 		if (*line != '\0')
// 		{
// 			append_error(g, "", "Invalid map, wrong data\n");
// 			free(line);
// 			line = NULL;
// 			break ;
// 		}
// 		free(line);
// 		line = NULL;
// 	}
// 	free(line);
// 	line = NULL;
// }

// void 	parse_map(char *line, t_global *g, t_list **list)
// {
// 	if (line[0] != 0)
// 	{
// 		ft_lstadd_back(list, ft_lstnew(ft_strdup(line)));
// 	}
// 	else if (line[0] == 0 && g->in_map)
// 			append_error(g, "", "Invalid map, empty line\n");
// }

// static void 	print_list(t_list *grid)
// {
// 	static int i = 0;
// 	if (i == 0)
// 		printf("Test record premiere ligne\n");
// 	else
// 		printf("Test record reste de la map\n");
// 	while (grid)
// 	{
// 		printf("%s\n", (char *)grid->content);
// 		grid = grid->next;
// 	}
// }

static void 	check_args_player(t_global *g)
{
	if (g->nb_player != 1)
		append_error(g, "", "Invalid number of player\n");

}

static void	check_player(t_global *g)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g->number_rows)
	{
		j = -1;
		while (++j < g->number_columns)
		{
			if (g->tab[i][j] == 'N' || g->tab[i][j] == 'S' ||
				g->tab[i][j] == 'E' || g->tab[i][j] == 'W')
			{
				g->nb_player += 1;
				g->player.pos.x = (float)i;
				g->player.pos.y = (float)j;
				g->pos_player = g->tab[i][j];
			}
		}
	}
	check_args_player(g);
}

void		parse_map(char *line, int fd, t_global *g, t_list **list)
{
	// g->tab = dual_realloc(g->tab, line);
	recovery_map(g, line, list);
	// print_list(list);
	fetch_map(g, line, fd, list);
	// print_list(list);
	// check_remaining_map_data(g, line, fd);
	if (!count_grid(g, *list))
		ft_lstclear(list, &ft_del_list);
	process_map(g);
	check_player(g);
}
