/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_error_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:44 by thhusser          #+#    #+#             */
/*   Updated: 2022/04/13 15:54:12 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	append_error(t_global *g, char *id, char *message)
{
	char	*res;

	res = ft_strjoin(id, message);
	record_error(g, res);
	free(res);
	res = NULL;
}
