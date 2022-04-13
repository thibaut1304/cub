/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_line_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:49 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/07 16:36:12 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	detect_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (*line == '\0')
		return (0);
	while (line[i])
	{
		if (is_in_charset(line[i], " 01NSEW") == 0)
			return (0);
		i++;
	}
	return (1);
}

int	count_sep_line(char *line)
{
	int	i;
	int	x;

	i = -1;
	x = 0;
	while (line[++i])
	{
		if (line[i] == ',')
			x++;
	}
	if (x > 2)
		return (1);
	return (0);
}
