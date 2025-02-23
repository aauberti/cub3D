/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:59:54 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/23 17:02:36 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	stock_color_f(t_data *data, char **color, bool *error)
{
	data->f_color->r = convert_string_to_long(color[0], error);
	data->f_color->g = convert_string_to_long(color[1], error);
	data->f_color->b = convert_string_to_long(color[2], error);
}

void	stock_color_c(t_data *data, char **color, bool *error)
{
	data->c_color->r = convert_string_to_long(color[0], error);
	data->c_color->g = convert_string_to_long(color[1], error);
	data->c_color->b = convert_string_to_long(color[2], error);
}
