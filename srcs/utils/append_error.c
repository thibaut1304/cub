/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:44 by thhusser          #+#    #+#             */
/*   Updated: 2021/11/22 11:51:43 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	append_error(t_global *g, char *id, char *message)
{
	char *res;

	res = ft_strjoin(id, message);
	// g->error = dual_realloc(g->error, res);
	record_error(g, &g->error, res);
	free(res);
	res = NULL;
}
