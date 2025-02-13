#ifndef CUB_H
# define CUB_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"

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

typedef struct s_param
{
	int		i;
	int		height;
	int		prev_len;
}		t_param;

//Parsing
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
void	free_string_array(char **array);
void	free_data(t_data *data);
bool	free_false(char *str);

#endif
