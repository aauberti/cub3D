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

static bool	split_rgb_F_color(t_data *data, char *rgb)
{
	char	*tmp;
	char	**color;
	bool	error;
	int		i;

	i = 0;
	error = true;
	tmp = ft_strtrim(rgb, WHITESPACES);
	color = ft_split(tmp, ',');
	while (color && color[i])
		i++;
	if (i != 3)
		return (false);
	if (!color)
		return (false);
	data->F_color->r = convert_string_to_long(color[0], &error);
	data->F_color->g = convert_string_to_long(color[1], &error);
	data->F_color->b = convert_string_to_long(color[2], &error);
	if (!error)
		return(false);
	return (true);
}

static bool	split_rgb_C_color(t_data *data, char *rgb)
{
	char	*tmp;
	char	**color;
	bool	error;
	int		i;

	i = 0;
	error = true;
	tmp = ft_strtrim(rgb, WHITESPACES);
	color = ft_split(tmp, ',');
	while (color && color[i])
		i++;
	if (i != 3)
		return (false);
	if (!color)
		return (false);
	data->C_color->r = convert_string_to_long(color[0], &error);
	data->C_color->g = convert_string_to_long(color[1], &error);
	data->C_color->b = convert_string_to_long(color[2], &error);
	if (!error)
		return(false);
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
		if (data->F_color->b != 0 || data->F_color->g != 0|| data->F_color->r != 0)
			return (false);
		tmp = ft_substr(line, i + 1, ft_strlen(&line[i]) - 1);
		if (!split_rgb_F_color(data, tmp))
			return (false);
	}
	else if (line[i] == 'C')
	{
		if (data->C_color->b != 0 || data->C_color->g != 0|| data->C_color->r != 0)
			return (false);
		tmp = ft_substr(line, i + 1, ft_strlen(&line[i]) - 1);
		if (!split_rgb_C_color(data, tmp))
			return (false);
	}
	return (true);
}
