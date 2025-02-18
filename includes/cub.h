/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:54:17 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/18 08:54:18 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

# define HEIGHT 1080

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_data
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	t_color	*f_color;
	t_color	*c_color;
	char	*map_line;
	char	**map;
}	t_data;

typedef struct s_window
{
	void	*mlx;
	void	*win_ptr;
	int		img_width;
	int		img_height;
	void	*img;
}	t_window;

typedef struct s_img
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
}	t_img;

typedef struct s_img_data
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_cub
{
	t_data		*data;
	t_window	win;
	t_img		img;
	t_ray		ray;
	t_keys		keys;
}	t_cub;

typedef struct s_param
{
	int	i;
	int	height;
	int	prev_len;
}	t_param;

typedef struct s_line_vars
{
	void	*texture;
	char	*tex_addr;
	int		tex_bpp;
	int		tex_line_len;
	int		tex_endian;
	double	wall_x;
	int		tex_x;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	double	step;
	double	tex_pos;
	int		x;
}	t_line_vars;

/* Main function prototypes */
void	init_cub(t_data *data);
int		end(t_cub *cub);
int		close_window(t_cub *cub);

/* Hooks */
void	setup_hooks(t_cub *cub);
void	move_player(t_cub *cub);
int		key_press(int keycode, t_cub *cub);
int		key_release(int keycode, t_cub *cub);
int		render(t_cub *cub);

/* Memory management */
void	free_images(t_cub *cub);
void	free_data(t_data *data);
void	free_string_array(char **array);
bool	free_false(char *str);

/* Drawing */
void	draw_walls(t_cub *cub);
void	draw_section(t_img_data *img_data, int y_start, int y_end, int color);
void	draw_vertical_line(t_cub *cub, int x, int start, int end);

/* Ray calculations */
void	calc_ray_pos(t_ray *ray, int x);
void	init_dda(t_ray *ray);
void	init_step_and_side_dist(t_ray *ray);
void	perform_dda(t_ray *ray, t_cub *cub);
void	calculate_wall_dist(t_ray *ray);
void	calculate_wall_height(t_ray *ray);

/* Texture management */
void	*get_texture(t_cub *cub, t_ray *ray);
void	calc_texture_x(t_ray *ray, double *wall_x, int *tex_x);

/* Initialization */
bool	init_img(t_cub *cub);
void	find_player_pos(t_cub *cub);

/* Parsing */
bool	check_param(int ac, char **av);
t_data	*init_data(int fd);
bool	valid_path(t_data *data, char *line);
bool	valid_color(t_data *data, char *line);
bool	valid_map(t_data *data, char *line);
t_data	*parse_map(t_data *data, char *line, int fd);
int		parse_file(t_data *data, char *line);
bool	valid_line(char *line);
bool	all_param_fill(t_data *data);
bool	fill_map(t_data *data);
int		check_cell(char **map, int j, int curr_len, t_param *param);
bool	ft_valid_char(char c, char *charset);
bool	error_in_map(t_data *data, char *tmp);
bool	valid_start(char *str);

#endif