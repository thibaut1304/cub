/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:52:33 by thhusser          #+#    #+#             */
/*   Updated: 2022/04/13 15:54:48 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	record_error(t_global *g, char *str)
{
	t_list	*new_error;

	g->nb_error += 1;
	new_error = ft_lstnew(ft_strdup(str));
	ft_lstadd_back(&g->error, new_error);
}

void	print_error(t_list *error)
{
	char	*line;

	line = NULL;
	ft_putstr("Error\n");
	while (error)
	{
		line = ft_strdup(error->content);
		ft_putstr(line);
		free(line);
		error = error->next;
	}
}
