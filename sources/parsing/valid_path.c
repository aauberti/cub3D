#include "cub.h"

static bool	valid_path_no(t_data *data, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		i = i + 2;
		if (data->path_NO)
			return (false);
		tmp = ft_substr(line, i, ft_strlen(&line[i]) - 1);
		if (!tmp)
			return (false);
		data->path_NO = ft_strtrim(tmp, " \n");
		free(tmp);
		if (!data->path_NO)
			return (false);
	}
	return (true);
}

static bool	valid_path_so(t_data *data, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'S' && line[i + 1] == 'O')
	{
		i = i + 2;
		if (data->path_SO)
			return (false);
		tmp = ft_substr(line, i, ft_strlen(&line[i]) - 1);
		if (!tmp)
			return (false);
		data->path_SO = ft_strtrim(tmp, " \n");
		free(tmp);
		if (!data->path_SO)
			return (false);
	}
	return (true);
}

static bool	valid_path_we(t_data *data, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'W' && line[i + 1] == 'E')
	{
		i = i + 2;
		if (data->path_WE)
			return (false);
		tmp = ft_substr(line, i, ft_strlen(&line[i]) - 1);
		if (!tmp)
			return (false);
		data->path_WE = ft_strtrim(tmp, " \n");
		free(tmp);
		if (!data->path_WE)
			return (false);
	}
	return (true);
}

static bool	valid_path_ea(t_data *data, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'E' && line[i + 1] == 'A')
	{
		i = i + 2;
		if (data->path_EA)
			return (false);
		tmp = ft_substr(line, i, ft_strlen(&line[i]) - 1);
		if (!tmp)
			return (false);
		data->path_EA = ft_strtrim(tmp, " \n");
		free(tmp);
		if (!data->path_EA)
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
