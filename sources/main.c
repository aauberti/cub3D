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
	printf("%d\n%d\n%d\n",data->F_color->r, data->F_color->g, data->F_color->b);
	printf("%d\n%d\n%d\n",data->C_color->r, data->C_color->g, data->C_color->b);
	//free_data !!!!!!!
	return (0);
}
