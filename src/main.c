#include "cub.h"

static void	error_path(t_cub *cub)
{
	ft_putstr_fd("Error\nProblem with the image or path\n", 2);
	free_images(cub);
	free_data(cub->data);
	mlx_destroy_display(cub->win.mlx);
	free(cub->win.mlx);
	free(cub);
	exit(0);
}

int	close_window(t_cub *cub)
{
	mlx_loop_end(cub->win.mlx);
	free_images(cub);
	mlx_destroy_window(cub->win.mlx, cub->win.win_ptr);
	mlx_destroy_display(cub->win.mlx);
	free(cub->win.mlx);
	free_data(cub->data);
	free(cub);
	exit(0);
	return (0);
}

static t_cub	*init_cub_struct(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	ft_memset(cub, 0, sizeof(t_cub));
	return (cub);
}

void	init_cub(t_data *data)
{
	t_cub	*cub;

	cub = init_cub_struct();
	if (!cub)
		return ;
	cub->data = data;
	cub->win.mlx = mlx_init();
	if (!cub->win.mlx)
	{
		free(cub);
		return ;
	}
	ft_memset(&cub->img, 0, sizeof(t_img));
	if (!init_img(cub))
		return (error_path(cub));
	cub->win.win_ptr = mlx_new_window(cub->win.mlx, 1920, HEIGHT, "cub3D");
	find_player_pos(cub);
	setup_hooks(cub);
	mlx_loop(cub->win.mlx);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		fd;

	if (!check_param(ac, av))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCan't open this file\n", 2);
		return (1);
	}
	data = init_data(fd);
	close(fd);
	if (!data)
		return (1);
	if (!fill_map(data))
		return (1);
	init_cub(data);
	free_data(data);
	return (0);
}
