/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:52:33 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/01 16:06:16 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	record_error(t_global *g, char *str)
{
	t_list	*new_error;

	g->nb_error += 1;
	new_error = ft_lstnew(ft_strdup(str));
	ft_lstadd_back(&error, new_error);
}

void	print_error(t_list *error)
{
	char	*line;

	line = NULL;
	while (error)
	{
		line = ft_strdup(error->content);
		ft_putstr("Error\n");
		ft_putstr(line);
		free(line);
		error = error->next;
	}
}

void	append_error(t_global *g, char *id, char *message)
{
	char *res;

	res = ft_strjoin(id, message);
	// g->error = dual_realloc(g->error, res);
	record_error(g, &g->error, res);
	free(res);
	res = NULL;
}