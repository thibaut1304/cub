/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:09 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/01 21:28:53 by thhusser         ###   ########.fr       */
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
		if (*line != 0)
			recovery_map(g, line, list);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd);
}

static void	pos_player(t_player *player, int x, int y, char orientation)
{
	if (player->pos.x == -1 && player->pos.y == -1)
	{
		player->pos.x = x + 0.55;
		player->pos.y = y + 0.55;
		if (orientation == 'N')
			player->rot_ang = 1.5 * M_PI;
		else if (orientation == 'S')
			player->rot_ang = M_PI / 2;
		else if (orientation == 'E')
			player->rot_ang = 0;
		else if (orientation == 'W')
			player->rot_ang = M_PI;
	}
}

static void		check_player(t_global *cub)
{
	int x;
	int y;
	int num_position;

	y = -1;
	num_position = 0;
	while (++y < cub->data.rows)
	{
		x = -1;
		while (++x < cub->data.cols)
		{
			if (ft_strchr("NSEW", cub->tab[y][x]))
			{
				pos_player(&cub->player, x, y, cub->tab[y][x]);
				num_position++;
				cub->tab[y][x] = '0';
				if (num_position > 1)
					append_error(cub, "", "Multiple player position in map\n");
			}
		}
	}
	printf("%d\n", num_position);
	printf("%d\n", cub->data.rows);
	if (num_position == 0)
		append_error(cub, "", "No player position in map\n");
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
	print_map(g);
	check_player(g);
}
