#ifndef CUB_H
# define CUB_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_color
{
	int r;
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
}	t_data;

//Parsing
bool	check_param(int ac, char **av);
t_data    *init_data(char *av);


#endif