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
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	t_color	*F;
	t_color	*C;
}	t_data;






//Parsing
bool	check_param(int ac, char **av);
bool	init_data(t_data *data, char *av);


#endif