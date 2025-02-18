/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:53:54 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/18 08:53:55 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free_ptr(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
		array = NULL;
	}
}

bool	free_false(char *str)
{
	free(str);
	return (false);
}

void	free_data(t_data *data)
{
	free(data->path_no);
	free(data->path_so);
	free(data->path_we);
	free(data->path_ea);
	free(data->c_color);
	free(data->f_color);
	free(data->map_line);
	free_string_array(data->map);
	free(data);
}
