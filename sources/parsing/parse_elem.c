#include "cub.h"

int	parse_file(t_data *data, char *line)
{
	if (line == NULL)
		return (0);
	else if (!all_param_fill(data))
	{
		if (valid_line(line))
		{
			if (!valid_path(data, line) || !valid_color(data, line))
				return (2);
		}
		else
			return (2);
	}
	else
		return (1);
	free(line);
	return (3);
}

t_data	*parse_map(t_data *data, char *line, int fd)
{
	char	*tmp;

	data->map_line = ft_strdup(line);
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tmp = ft_strjoin(data->map_line, line);
		free(line);
		free(data->map_line);
		data->map_line = ft_strdup(tmp);
		free(tmp);
	}
	return (data);
}
