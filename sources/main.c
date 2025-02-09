#include "cub.h"

int	main(int ac, char **av)
{
	t_data data;
	int		fd;

	if (!check_param(ac, av))
		return (1);
	init_data(&data, av[1]);
	return (0);
}