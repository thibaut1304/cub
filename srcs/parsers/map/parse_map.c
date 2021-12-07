/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:09 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/07 13:39:03 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

static void	recovery_map(t_global *g, char *line, t_list **list)
{
	t_list	*new_elem;

	if (*line == '\0')
		return ;
	g->in_map = 1;
	new_elem = ft_lstnew(ft_strdup(line));
	ft_lstadd_back(list, new_elem);
}

static void	fetch_map(t_global *g, char *line, int fd, t_list **list)
{
	int	res;

	res = 1;
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		if (!detect_map_line(line))
		{
			if (*line != '\0' || *line == '\t' || *line == 32)
			{
				append_error(g, "", "Invalid map, wrong data\n");
				break ;
			}
			ft_del_line(line);
			if (check_end_file(fd, res))
				record_error(g, "Invalid map, wrong data\n");
			close(fd);
			return ;
		}
		recovery_map(g, line, list);
		ft_del_line(line);
	}
	ft_del_line(line);
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

static void	check_player(t_global *cub)
{
	int	x;
	int	y;
	int	num_position;

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
	if (num_position == 0)
		append_error(cub, "", "No player position in map\n");
}

void	parse_map(char *line, int fd, t_global *g, t_list **list)
{
	recovery_map(g, line, list);
	fetch_map(g, line, fd, list);
	if ((g->valid_parameter_count != 6 || !g->in_map
			|| !g->new_line) && !g->error)
		record_error(g, "Invalid map, wrong data or no new line\n");
	if (!count_grid(g, *list))
		ft_lstclear(list, &ft_del_list);
	if (g->error)
		return ;
	process_map(g);
	check_player(g);
}
