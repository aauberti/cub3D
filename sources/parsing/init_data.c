#include "cub.h"

static t_data *create_and_init_data(void)
{
	t_data	*data;

    data = malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    ft_memset(data, 0, sizeof(t_data));
    data->C_color = malloc(sizeof(t_color));
    data->F_color = malloc(sizeof(t_color));
    if (!data->C_color || !data->F_color)
    {
        free(data->C_color);
        free(data->F_color);
        free(data);
        return (NULL);
    }
    ft_memset(data->C_color, 0, sizeof(t_color));
    ft_memset(data->F_color, 0, sizeof(t_color));
    return (data);
}

static bool	valid_param2(t_data *data, char *line)
{
    int i;

    i = 2;
    if (line[0] == 'W' && line[1] == 'E')
    {
        if (data->path_WE)
            return (false);
        while (ft_isspace(line[i]))
            i++;
        data->path_WE = ft_substr(line, i, ft_strlen(&line[i]) - 1);
        if (!data->path_WE)
            return (false);
    }
    else if (line[0] == 'E' && line[1] == 'A')
    {
        if (data->path_EA)
            return (false);
        while (ft_isspace(line[i]))
            i++;
        data->path_EA = ft_substr(line, i, ft_strlen(&line[i]) - 1);
        if (!data->path_EA)
            return (false);
    }
    return (true);
}

static bool	valid_param(t_data *data, char *line, int i)
{
    if (line[0] == 'N' && line[1] == 'O')
    {
        if (data->path_NO)
            return (false);
        while (ft_isspace(line[i]))
            i++;
        data->path_NO = ft_substr(line, i, ft_strlen(&line[i]) - 1);
        if (!data->path_NO)
            return (false);
    }
    else if (line[0] == 'S' && line[1] == 'O')
    {
        if (data->path_SO)
            return (false);
        while (ft_isspace(line[i]))
            i++;
        data->path_SO = ft_substr(line, i, ft_strlen(&line[i]) - 1);
        if (!data->path_SO)
            return (false);
    }
    else if (!valid_param2(data, line))
        return (false);
    return (true);
}

t_data    *init_data(char *av)
{
    t_data  *data;
    int     fd;
    char    *line;

    data = create_and_init_data();
    if (!data)
        return (NULL);
    fd = open(av, O_RDONLY);
    if (fd < 0)
        return (NULL);
    while(1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            return (data);
        if (!valid_param(data, line, 2)) 
        {
            ft_putstr_fd("Error\nBad element in the map file\n", 2);
            free(line);
            return (NULL);
        }
        free(line);
    }
}
