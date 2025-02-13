#include "cub.h"

bool	ft_valid_char(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool error_in_map(t_data *data , char *tmp)
{
	free(tmp);
	free_data(data);
	ft_putstr_fd("Error\nBad element in map\n", 2);
	return (false);
}

bool	fill_map(t_data *data)
{
	char    *tmp;
	int 	i;

	i = 0;
	tmp = ft_strtrim(data->map_line, "\n");
	if (!tmp)
		return (false);
	while (tmp && tmp[i])
	{
		if (!ft_valid_char(tmp[i], " \n01NSWE"))
			return (error_in_map(data, tmp));
		if (tmp[i] == '\n' && tmp[i + 1] == '\n')
		 	return (error_in_map(data, tmp));
		i++;
	}
	data->map = ft_split(tmp, '\n');
	free(tmp);
	if (!data->map)
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;

	if (!check_param(ac, av))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	data = init_data(fd);
	close(fd);
	if (!data)
		return (1);
	printf("%s\n%s\n%s\n%s\n", data->path_NO, data->path_SO, data->path_EA,
		data->path_WE);
	printf("%d\n%d\n%d\n", data->F_color->r, data->F_color->g,
		data->F_color->b);
	printf("%d\n%d\n%d\n", data->C_color->r, data->C_color->g,
		data->C_color->b);
	if (!fill_map(data))
		return (1);
	free_data(data);
	return (0);
}

	// printf("%s", data->map_line);
