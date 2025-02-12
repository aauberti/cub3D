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
	char	*path_NO;
	char	*path_SO;
	char	*path_WE;
	char	*path_EA;
	t_color	*F_color;
	t_color	*C_color;
	char	*map_line;
	char	**map;
}	t_data;

//Parsing
bool	check_param(int ac, char **av);
t_data   *init_data(int fd);
bool    valid_path(t_data *data, char *line);
bool	valid_color(t_data *data, char *line);
bool 	valid_map(t_data *data, char *line);
t_data	*parse_map(t_data *data, char *line, int fd);
int		parse_file(t_data *data, char *line);
bool	valid_line(char *line);
bool	all_param_fill(t_data *data);

//free
void	free_ptr(void *ptr);
void	free_string_array(char **array);
void	free_data(t_data *data);


#endif