/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:32:15 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/02 16:32:18 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x <= win->wid && y >= 0 && y <= win->hei)
	{
		dst = win->img.addr + (y * win->img.line_length + x *
				(win->img.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	rect(t_global *cub, t_pos a, t_pos b, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < b.x)
	{
		j = -1;
		while (++j < b.y)
			my_mlx_pixel_put(&cub->win, a.x + i, a.y + j, color);
	}
}

void	square(t_pos pos, int size, t_global *cub, int color)
{
	int		i;
	int		j;

	i = -1;
	while (++i <= size)
	{
		j = -1;
		while (++j <= size)
			my_mlx_pixel_put(&cub->win, pos.x + j, pos.y + i, color);
	}
}

void	render_line(t_line *line, t_global *cub, int color)
{
	t_pos		delta;
	t_pos		tmp;
	float		len;
	float		i;

	delta.x = line->end.x - line->start.x;
	delta.y = line->end.y - line->start.y;
	len = sqrt(delta.x * delta.x + delta.y * delta.y);
	tmp.x = delta.x / len;
	tmp.y = delta.y / len;
	delta.x = line->start.x;
	delta.y = line->start.y;
	i = -1;
	while (++i < len)
	{
		my_mlx_pixel_put(&cub->win, delta.x, delta.y, color);
		delta.x += tmp.x;
		delta.y += tmp.y;
	}
}
