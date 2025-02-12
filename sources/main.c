#include "cub.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

t_map *create_map(char *str)
{
    t_map   *map_info;
    int     i;
    int     j;
    int     lines;

	i = 0;
	j = 0;
	lines = 0;
    while (str[i])
    {
        if (str[i] == '\n')
        {
            if (str[i + 1] != '\0')
                lines++;
        }
        i++;
    }
    if (str[i - 1] != '\n')
        lines++;
    map_info = malloc(sizeof(t_map));
    if (!map_info)
        return NULL;
    map_info->height = lines;
    map_info->widths = malloc(sizeof(int) * lines);
    if (!map_info->widths)
    {
        free(map_info);
        return NULL;
    }
    map_info->map = malloc(sizeof(char *) * (lines + 1));
    if (!map_info->map)
    {
        free(map_info->widths);
        free(map_info);
        return NULL;
    }
    i = 0;
    lines = 0;
    while (str[i] && lines < map_info->height)
    {
        j = 0;
        while (str[i + j] && str[i + j] != '\n')
            j++;
        map_info->widths[lines] = j;
        map_info->map[lines] = malloc(sizeof(char) * (j + 1));
        if (!map_info->map[lines])
        {
            while (lines > 0)
                free(map_info->map[--lines]);
            free(map_info->map);
            free(map_info->widths);
            free(map_info);
            return NULL;
        }
        ft_strncpy(map_info->map[lines], &str[i], j);
        map_info->map[lines][j] = '\0';
        i += j;
        if (str[i] == '\n')
            i++;
        lines++;
    }
    map_info->map[lines] = NULL;
    return (map_info);
}

void free_map_struct(t_map *map_info)
{
    int i;

	i = 0;
    if (!map_info)
        return;
    if (map_info->map)
    {
        while (i < map_info->height)
        {
            if (map_info->map[i])
                free(map_info->map[i]);
			i++;
        }
        free(map_info->map);
    }
    if (map_info->widths)
        free(map_info->widths);
    free(map_info);
}

void print_map_with_size(t_map *map)
{
    int i;

    if (!map || !map->map)
    {
        printf("Map invalide\n");
        return;
    }
    printf("Map (hauteur: %d):\n", map->height);
    for (i = 0; i < map->height; i++)
        printf("[%2d] %s (%d)\n", i, map->map[i], map->widths[i]);
}

//ajout verif map + trim les \n du debut et la fin avant de faire la map
bool	fill_map(t_map *map, char *str)
{
	map = create_map(str);
	if (!map)
		return (false);
	print_map_with_size(map);
	free_map_struct(map);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;
	t_map	*map;

	map= NULL;
	if (!check_param(ac, av))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	data = init_data(fd);
	close(fd);
	if (!data)
		return (1);
	if (!fill_map(map, data->map_line))
		return (1);
	free_data(data);
	return (0);
}


	// printf("%s\n%s\n%s\n%s\n", data->path_NO, data->path_SO, data->path_EA,
	// 	data->path_WE);
	// printf("%d\n%d\n%d\n", data->F_color->r, data->F_color->g,
	// 	data->F_color->b);
	// printf("%d\n%d\n%d\n", data->C_color->r, data->C_color->g,
	// 	data->C_color->b);
	// printf("%s", data->map_line);