/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:29:46 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/07 16:35:58 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

# define KEY_Z		122
# define KEY_A		97
# define KEY_W		119
# define KEY_Q		113
# define KEY_S		115
# define KEY_D		100
# define KEY_UP		65362
# define KEY_LEFT	65361
# define KEY_DOWN	65364
# define KEY_RIGHT	65363
# define KEY_ESC	65307

# define V_GRAY	0x00E1E3E8
# define GRAY	0x00818591
# define BLUE	0x000000FF
# define WHITE	0x00FFFFFF
# define GREEN	0x0074B44A

# define CARDINAL_POINTS "NSEW"
# define MINIMAP_SCALE 10
# define FOV 1.04719755
# define TEXT 5

//MINIMAP
# define MINIMAP_H	100
# define MINIMAP_W	200
# define CENTER_X	100
# define CENTER_Y	50
# define DIST_PER_PIXEL	0.15

typedef struct s_pos
{
	float		x;
	float		y;
}				t_pos;

/* 0 == nord : 1 == sud : 2 == est : 3 == ouest : 4 == sprite*/
typedef struct s_player
{
	int			lateral_d;
	float		mov_speed;
	float		rot_speed;
	float		rot_ang;
	int			walk_d;
	int			turn_d;
	int			rot_d;
	t_pos		pos;
}				t_player;

typedef struct s_img
{
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*addr;
	void		*img;
	int			wid;
	int			hei;
}				t_img;

typedef struct s_line
{
	t_pos		start;
	t_pos		end;
}				t_line;

typedef struct s_win
{
	int			tot_rays;
	void		*mlx_p;
	void		*win_p;
	char		*name;
	t_img		img;
	int			hei;
	int			wid;
}				t_win;

typedef struct s_dcast
{
	int			found_wall;
	float		xinter;
	float		yinter;
	float		next_x;
	float		next_y;
	float		xstep;
	float		ystep;
	float		hit_x;
	float		hit_y;
}				t_dcast;

typedef struct s_ray
{
	int			found_hz_wall;
	int			found_vt_wall;
	float		wall_hit_x;
	float		wall_hit_y;
	int			was_vt_hit;
	int			is_right;
	int			is_left;
	int			is_down;
	int			is_up;
	float		ray_ang;
	int			top_px;
	int			bot_px;
	t_pos		vt_hit;
	t_pos		hz_hit;
	t_line		line;
	float		dist;
	int			id;
}				t_ray;

typedef struct s_text
{
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			*name;
	char			*data;
	void			*ptr;
	int				wid;
	int				hei;
}				t_text;

typedef struct s_data
{
	float			dist_pplane;
	int				grid_flag;
	int				txtr_err;
	int				num_sprt;
	int				floor;
	int				ceil;
	int				cols;
	int				rows;
	int				res;
}				t_data;

typedef struct s_sprt
{
	int			visibility;
	int			texture;
	int			top_px;
	int			bot_px;
	float		dist;
	t_pos		pos;
	float		ang;
	float		hei;
	int			id;
	float		pos_x;
}				t_sprt;

typedef struct s_map_textures
{
	char	*north_texture_path;
	char	*south_texture_path;
	char	*east_texture_path;
	char	*west_texture_path;
	char	*sprite_texture_path;
	int		floor_color;
	int		ceiling_color;
}				t_map_textures;

typedef struct s_global
{
	t_list			*error;
	t_list			*list;
	t_text			*text;
	t_player		player;
	char			**tab;
	t_ray			*rays;
	t_sprt			*sprt;
	t_data			data;
	t_win			win;
	int				in_map;
	int				valid_parameter_count;
	int				new_line;
	int				nb_texture;
	int				ray_load;
	int				sprt_load;
	int				mlx_load;
	int				nb_error;
	t_map_textures	map_textures;
	int				number_rows;
	int				number_columns;
	int				nb_player;
	int				pos_player;
	int				fd;
	int				res;
}					t_global;

//parseur
int		check_borders(t_global *g, int line_count, int largest_line);
int		check_walls(t_global *g, int row_count, int col_count);
void	parse_map(char *line, int fd, t_global *g, t_list **list);
char	*add_spaces(char *str, int largest_line);
void	process_map(t_global *g);
int		check_open_texture(char *file, t_global *g);
void	parse_line_paths(char **line_split, t_global *g);
void	parse_input(t_global *g, char *file, t_list **list);
void	parse_rgb(char *id, char **rgb_split, int *path_ptr, t_global *g);
int		count_sep_line(char *line);

//utils
void	append_error(t_global *g, char *id, char *message);
int		detect_map_line(char *line);
int		ft_is_number(char *str);
int		is_in_charset(char c, char *charset);
int		number_of_args(char **line);
int		is_valid_file(char *file, char *str);
void	preliminaire(t_global *g);
int		check_end_file(int fd, int res);
void	ft_del_line(char *line);

int		game_loop(t_global *cub);

//cast_hz
t_dcast	fill_hz_data(t_global *cub, t_ray *ray);
void	hz_cast(t_ray *ray, t_global *cub, int i);

//cast_ray
void	select_texture(t_ray *rays, float hz_dist, float vt_dist);
float	find_ray_dist(float hz_dist, float vt_dist);
float	find_ray_hit(float hz_dist, float vt_dist, float hz_hit, float vt_hit);
t_ray	cast(t_ray ray, t_global *cub);
void	cast_all_rays(t_global *cub);

//cast vertical
t_dcast	fill_vt_data(t_global *cub, t_ray *ray);
void	vt_cast(t_ray *ray, t_global *cub, int i);

//error
void	record_error(t_global *g, char *str);
void	print_error(t_list *error);

void	init_grid(t_global *cub);
void	free_grid(t_global *cub);

void	init_img(t_img *img);
void	free_img(t_global *cub);
void	load_img(t_win *win);

int		key_pressed(int key, t_global *cub);
int		key_released(int key, t_player *player);

int		count_grid(t_global *g, t_list *grid);
void	convert_grid(t_global *g, t_list *list);
int		count_cols(t_list *grid);

int		end_cub(t_global *cub);
void	load_cub(t_global *cub, char *file);
void	run_cub(t_global *cub);

void	init_player(t_player *player);
void	update(t_global *cub, t_player *player);

void	render_floor(t_global *cub, t_ray rays, int i);
void	render_ceil(t_global *cub, t_ray rays, int i);
void	render_wall(t_global *cub, int i, float wall_hei);
void	render_3d(t_global *cub);
int		render(t_global *cub);

void	free_old_texture(t_global *g, int nb_textures);
void	init_texture(t_text *textures);
void	free_texture(t_global *cub);
void	load_texture(t_global *g);

void	init_ray(t_ray *ray, float ray_ang);
t_line	init_line(t_pos a, t_pos b);
t_pos	init_pos(float x, float y);
void	ft_init_textures_map(t_map_textures *text);
void	init_cub(t_global *cub, char *map);

void	my_mlx_pixel_put(t_win *win, int x, int y, int color);
void	rect(t_global *cub, t_pos a, t_pos b, int color);
void	square(t_pos pos, int size, t_global *cub, int color);
void	render_line(t_line *line, t_global *cub, int color);

void	free_old_texture_norm(t_global *g, int nb_textures);
float	normalize(float ray_ang);
int		grid_is_wall(float x, float y, t_global *cub);
float	p_dist(float x1, float y1, float x2, float y2);
int		grep_color(t_text text, int x, int y);

void	init_win(t_win *win);
void	free_win(t_global *cub);
void	load_win(t_win *win);

void	render_2d(t_global *cub);
#endif
