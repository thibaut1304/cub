
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

void	load_new_texture(t_global *g)
{
	int	i;

	i = -1;
    g->textures = malloc(sizeof(t_texture) * g->nb_texture);
    if (!g->textures)
        return ;
    while (++i < g->nb_texture)
    {
        ft_init_textures(&g->textures[i]);
    }
	g->textures[0].name = ft_strdup(g->map_textures.north_texture_path);
	g->textures[1].name = ft_strdup(g->map_textures.south_texture_path);
	g->textures[2].name = ft_strdup(g->map_textures.east_texture_path);
	g->textures[3].name = ft_strdup(g->map_textures.west_texture_path);
	g->textures[4].name = ft_strdup("./textures/wood.xpm");
    if (g->nb_texture == TEXT)
	    g->textures[5].name = ft_strdup(g->map_textures.sprite_texture_path);
    i = -1;
	while (++i < g->nb_texture)
	{
		g->textures[i].ptr = mlx_xpm_file_to_image(g->window.mlx_ptr,
				g->textures[i].name, &g->textures[i].w, &g->textures[i].h);
        if (!g->textures[i].ptr)
        {
		    append_error(g, g->textures[i].name, " : bad texture content\n");
            break ;
        }
		g->textures[i].data = mlx_get_data_addr(g->textures[i].ptr,
				&g->textures[i].bits_per_pxl, &g->textures[i].line_length,
				&g->textures[i].endian);
	}
}

void	init_texture(t_global *cub)
{
	int i;

	i = 0;
	while (i < 5)
	{
		cub->text[i].ptr = NULL;
		cub->text[i].data = NULL;
		cub->text[i].name = NULL;
		cub->text[i].bits_per_pixel = 0;
		cub->text[i].line_length = 0;
		cub->text[i].endian = 0;
		cub->text[i].wid = 0;
		cub->text[i].hei = 0;
		i++;
	}
}

void	free_texture(t_global *cub)
{
	int i;

	i = -1;
	while (++i < 5)
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
}

int		load_texture(t_global *cub)
{
	int i;

	i = -1;
	while (++i < 5)
	{
		if (cub->text[i].name)
		{
			cub->text[i].ptr = mlx_xpm_file_to_image(cub->win.mlx_p,
				cub->text[i].name, &cub->text[i].wid, &cub->text[i].hei);
			if (!cub->text[i].ptr)
				return (is_error("Bad texture content"));
			cub->text[i].data = mlx_get_data_addr(cub->text[i].ptr,
				&cub->text[i].bits_per_pixel, &cub->text[i].line_length,
				&cub->text[i].endian);
		}
	}
	return (1);
}

/*
** Determine if the line will contain the path of a valid texture and
** try to open file related to it.
*/

int		is_texture(char **line_data, t_global *cub)
{
	int fd;
	int i;

	i = 0;
	if (!ft_strcmp(line_data[0], "SO") || !ft_strcmp(line_data[0], "EA") ||
			!ft_strcmp(line_data[0], "NO") || !ft_strcmp(line_data[0], "S") ||
			!ft_strcmp(line_data[0], "WE"))
	{
		fd = open(line_data[1], O_RDONLY);
		if (fd < 0)
		{
			cub->data.txtr_err = 1;
			return (is_error("Couldn't open a texture file or file missing"));
		}
		close(fd);
		while (line_data[i])
			i++;
		if (i != 2)
		{
			cub->data.txtr_err = 1;
			return (is_error("A texture has more parameters than expected"));
		}
		return (1);
	}
	return (0);
}

/*
** Check if texture isn't already declared and fill it the name with the path
** given.
*/

int		fill_texture(t_global *cub, char **line_data)
{
	int i;

	i = -1;
	if (!ft_strcmp(line_data[0], "NO"))
		i = 0;
	else if (!ft_strcmp(line_data[0], "SO"))
		i = 1;
	else if (!ft_strcmp(line_data[0], "WE"))
		i = 2;
	else if (!ft_strcmp(line_data[0], "EA"))
		i = 3;
	else if (!ft_strcmp(line_data[0], "S"))
		i = 4;
	if (i == -1)			//a check
		return (1);			// a check
	if (cub->text[i].name)
		return (is_error("A texture is declared twice"));
	cub->text[i].name = ft_strdup(line_data[1]);
	return (1);
}
