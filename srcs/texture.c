/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:31:49 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/02 16:32:03 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void free_old_texture(t_global *g, int nb_textures)
{
    free(g->map_textures.north_texture_path);
    g->map_textures.north_texture_path = NULL;
    free(g->map_textures.south_texture_path);
    g->map_textures.south_texture_path = NULL;
    free(g->map_textures.east_texture_path);
    g->map_textures.east_texture_path = NULL;
    free(g->map_textures.west_texture_path);
    g->map_textures.west_texture_path = NULL;
    if (nb_textures == TEXT)
    {
        free(g->map_textures.sprite_texture_path);
        g->map_textures.sprite_texture_path = NULL;
    }
}

void	init_texture(t_text *textures)
{
	textures->bits_per_pixel = 0;
	textures->line_length = 0;
	textures->endian = 0;
	textures->wid = 0;
	textures->hei = 0;
	textures->ptr = NULL;
	textures->data = NULL;
	textures->name = NULL;
}

void	free_texture(t_global *cub)
{
	int i;

	i = -1;
	while (++i < cub->nb_texture)
	{
		if (cub->text[i].name)
		{
			free(cub->text[i].name);
			cub->text[i].name = NULL;
		}
		if (cub->text[i].ptr)
		{
			mlx_destroy_image(cub->win.mlx_p, cub->text[i].ptr);
			cub->text[i].ptr = NULL;
			cub->text[i].data = NULL;
		}
	}
	free(cub->text);
}

void	load_texture(t_global *g)
{
	int	i;

	i = -1;
    g->text = malloc(sizeof(t_text) * g->nb_texture);
    if (!g->text)
        return ;
    while (++i < g->nb_texture)
    {
        init_texture(&g->text[i]);
    }
	g->text[0].name = ft_strdup(g->map_textures.north_texture_path);
	g->text[1].name = ft_strdup(g->map_textures.south_texture_path);
	g->text[2].name = ft_strdup(g->map_textures.east_texture_path);
	g->text[3].name = ft_strdup(g->map_textures.west_texture_path);
    if (g->nb_texture == TEXT)
	    g->text[4].name = ft_strdup(g->map_textures.sprite_texture_path);
    i = -1;
	while (++i < g->nb_texture)
	{
		g->text[i].ptr = mlx_xpm_file_to_image(g->win.mlx_p,
				g->text[i].name, &g->text[i].wid, &g->text[i].hei);
        if (!g->text[i].ptr)
        {
		    append_error(g, g->text[i].name, " : bad texture content\n");
            break ;
        }
		g->text[i].data = mlx_get_data_addr(g->text[i].ptr,
				&g->text[i].bits_per_pixel, &g->text[i].line_length,
				&g->text[i].endian);
	}
}