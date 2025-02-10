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
    ft_memset(data->C_color, -1, sizeof(t_color));
    ft_memset(data->F_color, -1, sizeof(t_color));
    return (data);
}

static bool    valid_line(char *line)
{
    int i;

    i = 0;
    while (line && line[i] && ft_isspace(line[i]))
        i++;
    if (line[i] == '\0')
        return (true);
    if (line[i] == 'N' && line[i + 1] == 'O')
        return (true);
    else if (line[i] == 'S' && line[i + 1] == 'O')
        return (true);
    else if (line[i] == 'W' && line[i + 1] == 'E')
        return (true);
    else if (line[i] == 'E' && line[i + 1] == 'A')
        return (true);
    else if (line[i] == 'F')
        return (true);
    else if (line[i] == 'C')
        return (true); 
    return (false);
}

static bool    all_param_fill(t_data *data)
{
    bool ret;

    ret = true;
    if (!data->path_EA && !data->path_NO && !data->path_SO && !data->path_WE)
        ret = false;
    if (data->C_color->r == -1 && data->C_color->g == -1 && data->C_color->b == -1)
        ret = false;
    if (data->F_color->r == -1 && data->F_color->g == -1 && data->F_color->b == -1)
        ret = false;
    return (ret);
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
        if (!all_param_fill(data))
        {
            if (valid_line(line))
            {
                if (!valid_path(data, line) || !valid_color(data, line)) 
                {
                    ft_putstr_fd("Error\nBad element in the map file\n", 2);
                    free(line);
                    return (NULL);
                }
            }
            else
            {
                ft_putstr_fd("Error\nBad element in the map file\n", 2);
                free(line);
                return (NULL);
            }
            free(line);
        }
        else
            printf("OKOK\n");
    }
}
