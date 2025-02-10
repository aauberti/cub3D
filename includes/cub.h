#ifndef CUB_H
# define CUB_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>

# define WHITESPACES " \t\v\r\f\n"

typedef struct s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;

typedef struct s_data
{
	char	*path_NO;
	char	*path_SO;
	char	*path_WE;
	char	*path_EA;
	t_color	*F_color;
	t_color	*C_color;
}	t_data;

//Parsing
bool	check_param(int ac, char **av);
t_data    *init_data(char *av);
bool	valid_path_NO(t_data *data, char *line);
bool	valid_path_SO(t_data *data, char *line);
bool	valid_path_EA(t_data *data, char *line);
bool	valid_path_WE(t_data *data, char *line);

bool	valid_color(t_data *data, char *line);


#endif