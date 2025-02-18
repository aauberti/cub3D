/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:53:43 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/18 08:53:44 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	error_in_map(t_data *data, char *tmp)
{
	free(tmp);
	free_data(data);
	ft_putstr_fd("Error\nBad element in map\n", 2);
	return (false);
}

bool	valid_start(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		if (ft_valid_char(str[i], "NSWE"))
			count++;
		i++;
	}
	if (count != 1)
		return (false);
	return (true);
}
