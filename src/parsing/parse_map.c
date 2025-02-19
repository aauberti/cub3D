/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:53:46 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/19 12:03:16 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	check_line(char **map, t_param *param)
{
	int	j;
	int	curr_len;

	curr_len = ft_strlen(map[param->i]);
	j = 0;
	while (j < curr_len)
	{
		if (!check_cell(map, j, curr_len, param))
			return (0);
		j++;
	}
	return (curr_len);
}

static int	check_map(char **map)
{
	t_param	*param;

	if (!map || !map[0])
		return (0);
	param = malloc(sizeof(t_param));
	if (!param)
		return (0);
	param->height = 0;
	while (map[param->height])
		param->height++;
	param->i = 0;
	param->prev_len = ft_strlen(map[0]);
	while (param->i < param->height)
	{
		param->prev_len = check_line(map, param);
		if (param->prev_len == 0)
		{
			free(param);
			return (0);
		}
		param->i++;
	}
	free(param);
	return (1);
}

static bool	error_open_map(t_data *data)
{
	free_data(data);
	ft_putstr_fd("Error\nMap open\n", 2);
	return (false);
}

bool	fill_map(t_data *data)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strtrim(data->map_line, "\n");
	if (!tmp)
		return (false);
	while (tmp && tmp[i])
	{
		if (!valid_start(tmp))
			return (error_in_map(data, tmp));
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
	if (!check_map(data->map))
		return (error_open_map(data));
	return (true);
}
