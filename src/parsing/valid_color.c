/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:53:41 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/23 17:02:30 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	while (tmp[i++])
		if (tmp[i] == ',' && tmp[i + 1] == ',')
			return (free_false(tmp));
	i = 0;
	color = ft_split(tmp, ',');
	free(tmp);
	while (color && color[i])
		i++;
	if (!color || i != 3)
		return (free_string_array(color));
	stock_color_f(data, color, &error);
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
	while (tmp[i++])
		if (tmp[i] == ',' && tmp[i + 1] == ',')
			return (free_false(tmp));
	i = 0;
	color = ft_split(tmp, ',');
	free(tmp);
	while (color && color[i])
		i++;
	if (!color || i != 3)
		return (free_string_array(color));
	stock_color_c(data, color, &error);
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
	while (line[i] == ' ')
		i++;
	if (line[i] == 'F')
	{
		if (data->f_color->b != -1 || data->f_color->g != -1
			|| data->f_color->r != -1)
			return (false);
		tmp = ft_substr(line, i + 1, ft_strlen(&line[i]) - 1);
		if (!split_rgb_f_color(data, tmp, 0))
			return (false);
	}
	else if (line[i] == 'C')
	{
		if (data->c_color->b != -1 || data->c_color->g != -1
			|| data->c_color->r != -1)
			return (false);
		tmp = ft_substr(line, i + 1, ft_strlen(&line[i]) - 1);
		if (!split_rgb_c_color(data, tmp, 0))
			return (false);
	}
	return (true);
}
