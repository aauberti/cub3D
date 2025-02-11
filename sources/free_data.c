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
			if (array[i])
			{
				free_ptr(array[i]);
				array[i] = NULL;
			}
			i++;
		}
		free(array);
		array = NULL;
	}
}

void free_data(t_data *data)
{
	free(data->path_NO);
	free(data->path_SO);
	free(data->path_WE);
	free(data->path_EA);
	free(data->C_color);
	free(data->F_color);
	free(data);
}