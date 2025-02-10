#include "cub.h"

bool	check_param(int ac, char **av)
{
	int	len;
	char *ext;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (false);
	}
	len = ft_strlen(av[1]);
	if (len < 5)
	{
		ft_putstr_fd("Error\nUse a .cub file\n", 2);
		return (false);
	}
	ext = ft_substr(av[1], len - 4, 4);
	if (ft_strcmp(ext, ".cub"))
	{
		free(ext);
		ft_putstr_fd("Error\nUse a .cub file\n", 2);
		return (false);
	}
	free(ext);
	return (true);
}
