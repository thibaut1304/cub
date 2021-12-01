/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:17 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/01 19:16:31 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

static void	free_all(char **str)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

static void	rgb_to_hex(char *rgb_str, char *id, int *path_ptr, t_global *global)
{
	unsigned int	t;
	int				r;
	int				g;
	int				b;
	char			**rgb_split;

	t = 0;
	rgb_split = ft_split(rgb_str, (','));
	r = ft_atoi(rgb_split[0]);
	g = ft_atoi(rgb_split[1]);
	b = ft_atoi(rgb_split[2]);
	if (!(r >= 0 && r < 256 && g >= 0 && g < 256 && b >= 0 && b < 256))
		append_error(global, id, " : valid RGB range is [0 - 255]\n");
	if (*path_ptr == -1)
		*path_ptr = (t << 24 | r << 16 | g << 8 | b);
	else
		append_error(global, id, " : Already set\n");
	free_all(rgb_split);
	return ;
}

static void	parse_rgb(char *id, char *rgb_str, int *path_ptr, t_global *g)
{
	char **rgb_split;

	rgb_split = ft_split(rgb_str, ',');
	if (number_of_args(rgb_split) == 3)
	{
		if (ft_is_number(rgb_split[0]))
			if (ft_is_number(rgb_split[1]))
				if (ft_is_number(rgb_split[2]))
				{
					rgb_to_hex(rgb_str, id, path_ptr, g);
					g->valid_parameter_count++;
					free_all(rgb_split);
					return ;
				}
		append_error(g, id, " : only takes positive numbers\n");
		free_all(rgb_split);
		return ;
	}
	append_error(g, id, " : needs 3 numbers [0 -255]\n");
	free_all(rgb_split);
	return ;
}

static void	process_path(char **line_split, char **path_ptr, t_global *g)
{
	if (!path_ptr)
		return ;
	if (*path_ptr == NULL)
	{
		*path_ptr = ft_strdup(line_split[1]);
		g->valid_parameter_count++;
	}
	else
		append_error(g, line_split[0], " : path already set\n");
}

int		check_open_texture(char *file, t_global *g)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		append_error(g, file, " : impossible to open it !\n");
		return (1);
	}
	close(fd);
	fd = open(file, O_DIRECTORY);
    if (!(fd < 0))
	{
		append_error(g, file, " : file is directory\n");
		return (1);
	}
    close(fd);
	return (0);
}

void		parse_line_paths(char **line_split, t_global *g)
{
	if (!line_split)
		return ;
	if (ft_strcmp(line_split[0], "NO") == 0)
		process_path(line_split, &(g->map_textures.north_texture_path), g);
	else if (ft_strcmp(line_split[0], "SO") == 0)
		process_path(line_split, &(g->map_textures.south_texture_path), g);
	else if (ft_strcmp(line_split[0], "WE") == 0)
		process_path(line_split, &(g->map_textures.west_texture_path), g);
	else if (ft_strcmp(line_split[0], "EA") == 0)
		process_path(line_split, &(g->map_textures.east_texture_path), g);
	else if (ft_strcmp(line_split[0], "S") == 0)
		process_path(line_split, &(g->map_textures.sprite_texture_path), g);
	else if (ft_strcmp(line_split[0], "F") == 0)
		parse_rgb("F", line_split[1], &(g->data.floor), g);
	else if (ft_strcmp(line_split[0], "C") == 0)
		parse_rgb("C", line_split[1], &(g->data.ceil), g);
	else
		append_error(g, line_split[0], " wrong parameter ID\n");
}
