/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:07:14 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/03 14:36:23 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	number_of_args(char **line)
{
	int	i;

	if (!line)
		return (0);
	if (!(*line))
		return (0);
	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	is_valid_file(char *file, char *str)
{
	int		i;

	i = 0;
	while (file[i] != '\0')
		i++;
	i -= 4;
	if (i > 0)
		return (ft_strequ(&file[i], str));
	else
		return (0);
}
