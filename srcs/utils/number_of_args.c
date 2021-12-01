/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:07:14 by thhusser          #+#    #+#             */
/*   Updated: 2021/05/17 19:07:14 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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
