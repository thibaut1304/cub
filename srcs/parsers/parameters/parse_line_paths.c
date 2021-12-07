/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:17 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/07 20:16:21 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

static void	free_all(char **str)
{
	int	i;

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

static void	rgb_to_hex(char **rp, char *id, int *path_ptr, t_global *global)
{
	unsigned int	t;
	int				r;
	int				g;
	int				b;

	t = 0;
	r = ft_atoi(rp[1]);
	g = ft_atoi(rp[2]);
	b = ft_atoi(rp[3]);
	if (!(r >= 0 && r < 256 && g >= 0 && g < 256 && b >= 0 && b < 256))
		append_error(global, id, " : valid RGB range is [0 - 255]\n");
	if (*path_ptr == -1)
		*path_ptr = (t << 24 | r << 16 | g << 8 | b);
	else
		append_error(global, id, " : Already set\n");
	return ;
}

void	parse_rgb(char *id, char **rgb_split, int *path_ptr, t_global *g)
{
	if (number_of_args(rgb_split) == 4)
	{
		if (ft_is_number(rgb_split[1]))
		{
			if (ft_is_number(rgb_split[2]))
			{
				if (ft_is_number(rgb_split[3]))
				{
					rgb_to_hex(rgb_split, id, path_ptr, g);
					g->valid_parameter_count++;
					free_all(rgb_split);
					return ;
				}
			}
		}
		append_error(g, id, " : only takes positive numbers\n");
		free_all(rgb_split);
		return ;
	}
	append_error(g, id, " : needs 3 numbers [0 - 255]\n");
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

void	parse_line_paths(char **line_split, t_global *g)
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
	else if (!ft_strcmp(line_split[0], "F") && !ft_strcmp(line_split[0], "C"))
		append_error(g, line_split[0], " wrong parameter ID\n");
}
