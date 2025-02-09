#include "cub.h"

int	main(int ac, char **av)
{
	t_data *data;

	if (!check_param(ac, av))
		return (1);
	data = init_data(av[1]);
	if (!data)
		return (1);
	printf("%s\n%s\n%s\n%s\n", data->path_NO, data->path_SO, data->path_EA, data->path_WE);
	//free_data !!!!!!!
	return (0);
}
