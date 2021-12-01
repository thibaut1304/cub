/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dual_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:54 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/01 19:23:33 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

char	**dual_realloc(char **double_ptr, char *line)
{
	int		i;
	int		j;
	char	**res;
	int		line_count;

	i = 0;
	j = 0;
	line_count = number_of_args(double_ptr);
	res = malloc(sizeof(char *) * (line_count + 2));
	if (!res)
		return (NULL);
	while (i < line_count)
	{
		res[j] = ft_strdup(double_ptr[i]);
		free(double_ptr[i]);
		double_ptr[i] = NULL;
		i++;
		j++;
	}
	res[line_count] = ft_strdup(line);
	res[line_count + 1] = NULL;
	free(double_ptr);
	double_ptr = NULL;
	return (res);
}
