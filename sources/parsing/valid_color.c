#include "cub.h"

static int	convert_string_to_long(const char *str, bool *error)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			*error = false;
			break ;
		}
		nbr = (nbr * 10) + (str[i] - '0');
		if (nbr > 255 || nbr < 0)
		{
			*error = false;
			break ;
		}
		i++;
	}
	return (nbr);
}

static bool	split_rgb_f_color(t_data *data, char *rgb, int i)
{
	char	*tmp;
	char	**color;
	bool	error;

	error = true;
	tmp = ft_strtrim(rgb, " \n");
	free(rgb);
	if (!tmp || (tmp[0] && (tmp[0] == ',' || tmp[ft_strlen(tmp) -1] == ',')))
		return (free_false(tmp));
	color = ft_split(tmp, ',');
	free(tmp);
	while (color && color[i])
		i++;
	if (!color || i != 3)
	{
		free_string_array(color);
		return (false);
	}
	data->F_color->r = convert_string_to_long(color[0], &error);
	data->F_color->g = convert_string_to_long(color[1], &error);
	data->F_color->b = convert_string_to_long(color[2], &error);
	free_string_array(color);
	if (!error)
		return (false);
	return (true);
}

static bool	split_rgb_c_color(t_data *data, char *rgb, int i)
{
	char	*tmp;
	char	**color;
	bool	error;

	error = true;
	tmp = ft_strtrim(rgb, " \n");
	free(rgb);
	if (!tmp || (tmp[0] && (tmp[0] == ',' || tmp[ft_strlen(tmp) -1] == ',')))
		return (free_false(tmp));
	color = ft_split(tmp, ',');
	free(tmp);
	while (color && color[i])
		i++;
	if (!color || i != 3)
	{
		free_string_array(color);
		return (false);
	}
	data->C_color->r = convert_string_to_long(color[0], &error);
	data->C_color->g = convert_string_to_long(color[1], &error);
	data->C_color->b = convert_string_to_long(color[2], &error);
	free_string_array(color);
	if (!error)
		return (false);
	return (true);
}

bool	valid_color(t_data *data, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'F')
	{
		if (data->F_color->b != -1 || data->F_color->g != -1
			|| data->F_color->r != -1)
			return (false);
		tmp = ft_substr(line, i + 1, ft_strlen(&line[i]) - 1);
		if (!split_rgb_f_color(data, tmp, 0))
			return (false);
	}
	else if (line[i] == 'C')
	{
		if (data->C_color->b != -1 || data->C_color->g != -1
			|| data->C_color->r != -1)
			return (false);
		tmp = ft_substr(line, i + 1, ft_strlen(&line[i]) - 1);
		if (!split_rgb_c_color(data, tmp, 0))
			return (false);
	}
	return (true);
}
