#include "cub.h"

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;

	if (!check_param(ac, av))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCan't open this file\n", 2);
		return (1);
	}
	data = init_data(fd);
	close(fd);
	if (!data)
		return (1);
	if (!fill_map(data))
		return (1);
	free_data(data);
	return (0);
}

	// printf("%s\n%s\n%s\n%s\n", data->path_NO, data->path_SO, data->path_EA,
	// 	data->path_WE);
	// printf("%d\n%d\n%d\n", data->F_color->r, data->F_color->g,
	// 	data->F_color->b);
	// printf("%d\n%d\n%d\n", data->C_color->r, data->C_color->g,
	// 	data->C_color->b);
	// printf("%s", data->map_line);
