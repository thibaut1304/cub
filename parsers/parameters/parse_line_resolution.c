/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_resolution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:06:25 by thhusser          #+#    #+#             */
/*   Updated: 2021/11/19 16:36:28 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

// void	parse_line_resolution(char **line_split, t_global *g)
// {
// 	if (ft_strcmp(line_split[0], "R") == 0)
// 	{
// 		if (g->window->x_resolution >= 0 || g->window->y_resolution >= 0)
// 			append_error(g, "", "Resolution already set\n");
// 		else if ((ft_is_number(line_split[1]) && ft_is_number(line_split[2])))
// 		{
// 			g->window->x_resolution = ft_atoi(line_split[1]);
// 			g->window->y_resolution = ft_atoi(line_split[2]);
// 			if (g->window->x_resolution <= 0 || g->window->y_resolution <= 0)
// 			{
// 				append_error(g, "", "Resolution must be greater than 0\n");
// 				g->window->x_resolution = 0;
// 				g->window->y_resolution = 0;
// 				return ;
// 			}
// 			g->valid_parameter_count++;
// 			return ;
// 		}
// 		else
// 			append_error(g, "", "Resolution takes positive numbers only\n");
// 		return ;
// 	}
// 	append_error(g, "", "Wrong paramter ID\n");
// 	return ;
// }
