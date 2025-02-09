#include "cub.h"

bool	init_data(t_data *data, char *av)
{
	int 	fd;
	char 	*line;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return ;
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (true);
		if (!valid_param(&data, line))
		{
			ft_putstr_fd("Error\nBad element in the map file\n", 2);
			return (false);
		}
	}
}
