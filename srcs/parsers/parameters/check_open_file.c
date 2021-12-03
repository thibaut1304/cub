/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:07:46 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/03 11:17:39 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

int	check_open_texture(char *file, t_global *g)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		append_error(g, file, " : impossible to open it !\n");
		return (1);
	}
	if (fd >= 0)
		close(fd);
	fd = open(file, O_DIRECTORY);
	if (!(fd < 0))
	{
		append_error(g, file, " : file is directory\n");
		return (1);
	}
	if (fd >= 0)
		close(fd);
	return (0);
}
