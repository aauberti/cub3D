#include "cub.h"

static t_data	*create_and_init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_memset(data, 0, sizeof(t_data));
	data->c_color = malloc(sizeof(t_color));
	data->f_color = malloc(sizeof(t_color));
	if (!data->c_color || !data->f_color)
	{
		free(data->c_color);
		free(data->f_color);
		free(data);
		return (NULL);
	}
	ft_memset(data->c_color, -1, sizeof(t_color));
	ft_memset(data->f_color, -1, sizeof(t_color));
	data->map_line = NULL;
	return (data);
}

bool	valid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\n'))
		i++;
	if (line[i] == '\0')
		return (true);
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (true);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (true);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (true);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (true);
	else if (line[i] == 'F')
		return (true);
	else if (line[i] == 'C')
		return (true);
	return (false);
}

bool	all_param_fill(t_data *data)
{
	bool	ret;

	ret = true;
	if (!data->path_ea || !data->path_no || !data->path_so || !data->path_we)
		ret = false;
	if (data->c_color->r == -1 && data->c_color->g == -1
		&& data->c_color->b == -1)
		ret = false;
	if (data->f_color->r == -1 && data->f_color->g == -1
		&& data->f_color->b == -1)
		ret = false;
	return (ret);
}

void	*error_element(t_data *data, char *line)
{
	ft_putstr_fd("Error\nBad element in the map file\n", 2);
	free(line);
	free_data(data);
	return (NULL);
}

t_data	*init_data(int fd)
{
	char	*line;
	t_data	*data;
	int		res;

	data = create_and_init_data();
	if (!data)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		res = parse_file(data, line);
		if (res == 0)
			break ;
		else if (res == 1)
		{
			data = parse_map(data, line, fd);
			break ;
		}
		else if (res == 2)
			return (error_element(data, line));
		else
			continue ;
	}
	return (data);
}
