/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:44 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/02 16:54:14 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	append_error(t_global *g, char *id, char *message)
{
	char *res;

	res = ft_strjoin(id, message);
	record_error(g, res);
	free(res);
	res = NULL;
}
