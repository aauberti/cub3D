#include "cub.h"

static bool	valid_path_no(t_data *data, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		i = i + 2;
		if (data->path_no)
			return (false);
		tmp = ft_substr(line, i, ft_strlen(&line[i]) - 1);
		if (!tmp)
			return (false);
		data->path_no = ft_strtrim(tmp, " \n");
		free(tmp);
		if (!data->path_no)
			return (false);
	}
	return (true);
}

static bool	valid_path_so(t_data *data, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'S' && line[i + 1] == 'O')
	{
		i = i + 2;
		if (data->path_so)
			return (false);
		tmp = ft_substr(line, i, ft_strlen(&line[i]) - 1);
		if (!tmp)
			return (false);
		data->path_so = ft_strtrim(tmp, " \n");
		free(tmp);
		if (!data->path_so)
			return (false);
	}
	return (true);
}

static bool	valid_path_we(t_data *data, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'W' && line[i + 1] == 'E')
	{
		i = i + 2;
		if (data->path_we)
			return (false);
		tmp = ft_substr(line, i, ft_strlen(&line[i]) - 1);
		if (!tmp)
			return (false);
		data->path_we = ft_strtrim(tmp, " \n");
		free(tmp);
		if (!data->path_we)
			return (false);
	}
	return (true);
}

static bool	valid_path_ea(t_data *data, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'E' && line[i + 1] == 'A')
	{
		i = i + 2;
		if (data->path_ea)
			return (false);
		tmp = ft_substr(line, i, ft_strlen(&line[i]) - 1);
		if (!tmp)
			return (false);
		data->path_ea = ft_strtrim(tmp, " \n");
		free(tmp);
		if (!data->path_ea)
			return (false);
	}
	return (true);
}

bool	valid_path(t_data *data, char *line)
{
	if (!valid_path_so(data, line) || !valid_path_no(data, line)
		|| !valid_path_ea(data, line) || !valid_path_we(data, line))
		return (false);
	return (true);
}
