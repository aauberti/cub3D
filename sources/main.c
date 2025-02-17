#include "cub.h"

void	free_images(t_cub *cub)
{
	if (cub->img.north)
		mlx_destroy_image(cub->win.mlx, cub->img.north);
	if (cub->img.south)
		mlx_destroy_image(cub->win.mlx, cub->img.south);
	if (cub->img.east)
		mlx_destroy_image(cub->win.mlx, cub->img.east);
	if (cub->img.west)
		mlx_destroy_image(cub->win.mlx, cub->img.west);
	if (cub->win.img)
		mlx_destroy_image(cub->win.mlx, cub->win.img);
}

int	end(t_cub *cub)
{
	free_images(cub);
	free_data(cub->data);
	mlx_destroy_window(cub->win.mlx, cub->win.win_ptr);
	mlx_destroy_display(cub->win.mlx);
	free(cub->win.mlx);
	free(cub);
	exit(0);
}

bool	init_img(t_cub *cub)
{
	cub->img.north = mlx_xpm_file_to_image(cub->win.mlx, cub->data->path_no,
			&cub->win.img_width, &cub->win.img_height);
	if (!cub->img.north)
		return (false);
	cub->img.south = mlx_xpm_file_to_image(cub->win.mlx, cub->data->path_so,
			&cub->win.img_width, &cub->win.img_height);
	if (!cub->img.south)
		return (false);
	cub->img.east = mlx_xpm_file_to_image(cub->win.mlx, cub->data->path_ea,
			&cub->win.img_width, &cub->win.img_height);
	if (!cub->img.east)
		return (false);
	cub->img.west = mlx_xpm_file_to_image(cub->win.mlx, cub->data->path_we,
			&cub->win.img_width, &cub->win.img_height);
	if (!cub->img.west)
		return (false);
	return (true);
}

void	draw_section(t_img_data *img_data, int y_start, int y_end, int color)
{
	int	x;
	int	y;
	int	pixel;

	y = y_start;
	while (y < y_end)
	{
		x = 0;
		while (x < 1920)
		{
			pixel = y * img_data->line_length + x * (img_data->bits_per_pixel
					/ 8);
			img_data->addr[pixel] = color & 0xFF;
			img_data->addr[pixel + 1] = (color >> 8) & 0xFF;
			img_data->addr[pixel + 2] = (color >> 16) & 0xFF;
			x++;
		}
		y++;
	}
}

void	error_path(t_cub *cub)
{
	ft_putstr_fd("Error\nProblem with the image or path\n", 2);
	free_images(cub);
	free_data(cub->data);
	mlx_destroy_display(cub->win.mlx);
	free(cub->win.mlx);
	free(cub);
	exit(0);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == 119)
		cub->keys.w = 1;
	if (keycode == 115)
		cub->keys.s = 1;
	if (keycode == 97)
		cub->keys.a = 1;
	if (keycode == 100)
		cub->keys.d = 1;
	if (keycode == 65363)
		cub->keys.left = 1;
	if (keycode == 65361)
		cub->keys.right = 1;
	if (keycode == 65307)
		end(cub);
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == 119)
		cub->keys.w = 0;
	if (keycode == 115)
		cub->keys.s = 0;
	if (keycode == 97)
		cub->keys.a = 0;
	if (keycode == 100)
		cub->keys.d = 0;
	if (keycode == 65363)
		cub->keys.left = 0;
	if (keycode == 65361)
		cub->keys.right = 0;
	return (0);
}

void	move_player(t_cub *cub)
{
	double	move_speed;
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	move_speed = 0.049;
	rot_speed = 0.1;
	if (cub->keys.w)
	{
		if (cub->data->map[(int)(cub->ray.pos_y)][(int)(cub->ray.pos_x
				+ cub->ray.dir_x * move_speed)] != '1')
			cub->ray.pos_x += cub->ray.dir_x * move_speed;
		if (cub->data->map[(int)(cub->ray.pos_y + cub->ray.dir_y
				* move_speed)][(int)(cub->ray.pos_x)] != '1')
			cub->ray.pos_y += cub->ray.dir_y * move_speed;
	}
	if (cub->keys.s)
	{
		if (cub->data->map[(int)(cub->ray.pos_y)][(int)(cub->ray.pos_x
				- cub->ray.dir_x * move_speed)] != '1')
			cub->ray.pos_x -= cub->ray.dir_x * move_speed;
		if (cub->data->map[(int)(cub->ray.pos_y - cub->ray.dir_y
				* move_speed)][(int)(cub->ray.pos_x)] != '1')
			cub->ray.pos_y -= cub->ray.dir_y * move_speed;
	}
	if (cub->keys.d)
	{
		if (cub->data->map[(int)(cub->ray.pos_y)][(int)(cub->ray.pos_x
				- cub->ray.dir_y * move_speed)] != '1')
			cub->ray.pos_x -= cub->ray.dir_y * move_speed;
		if (cub->data->map[(int)(cub->ray.pos_y + cub->ray.dir_x
				* move_speed)][(int)(cub->ray.pos_x)] != '1')
			cub->ray.pos_y += cub->ray.dir_x * move_speed;
	}
	if (cub->keys.a)
	{
		if (cub->data->map[(int)(cub->ray.pos_y)][(int)(cub->ray.pos_x
				+ cub->ray.dir_y * move_speed)] != '1')
			cub->ray.pos_x += cub->ray.dir_y * move_speed;
		if (cub->data->map[(int)(cub->ray.pos_y - cub->ray.dir_x
				* move_speed)][(int)(cub->ray.pos_x)] != '1')
			cub->ray.pos_y -= cub->ray.dir_x * move_speed;
	}
	if (cub->keys.right)
	{
		old_dir_x = cub->ray.dir_x;
		cub->ray.dir_x = cub->ray.dir_x * cos(-rot_speed) - cub->ray.dir_y
			* sin(-rot_speed);
		cub->ray.dir_y = old_dir_x * sin(-rot_speed) + cub->ray.dir_y
			* cos(-rot_speed);
		old_plane_x = cub->ray.plane_x;
		cub->ray.plane_x = cub->ray.plane_x * cos(-rot_speed) - cub->ray.plane_y
			* sin(-rot_speed);
		cub->ray.plane_y = old_plane_x * sin(-rot_speed) + cub->ray.plane_y
			* cos(-rot_speed);
	}
	if (cub->keys.left)
	{
		old_dir_x = cub->ray.dir_x;
		cub->ray.dir_x = cub->ray.dir_x * cos(rot_speed) - cub->ray.dir_y
			* sin(rot_speed);
		cub->ray.dir_y = old_dir_x * sin(rot_speed) + cub->ray.dir_y
			* cos(rot_speed);
		old_plane_x = cub->ray.plane_x;
		cub->ray.plane_x = cub->ray.plane_x * cos(rot_speed) - cub->ray.plane_y
			* sin(rot_speed);
		cub->ray.plane_y = old_plane_x * sin(rot_speed) + cub->ray.plane_y
			* cos(rot_speed);
	}
}

int	render(t_cub *cub)
{
	void	*old_img;

	old_img = cub->win.img;
	cub->win.img = mlx_new_image(cub->win.mlx, 1920, HEIGHT);
	if (!cub->win.img)
		return (1);
	move_player(cub);
	draw_walls(cub);
	if (old_img)
		mlx_destroy_image(cub->win.mlx, old_img);
	return (0);
}

static int	close_window(t_cub *cub)
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

void	init_cub(t_data *data)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return ;
	ft_memset(cub, 0, sizeof(t_cub));
	cub->data = data;
	cub->win.mlx = mlx_init();
	if (!cub->win.mlx)
		return ;
	ft_memset(&cub->img, 0, sizeof(t_img));
	if (!init_img(cub))
		return (error_path(cub));
	if (!cub->win.mlx)
		return (free(cub));
	cub->win.win_ptr = mlx_new_window(cub->win.mlx, 1920, HEIGHT, "cub3D");
	find_player_pos(cub);
	mlx_hook(cub->win.win_ptr, 17, 0, close_window, cub);
	mlx_hook(cub->win.win_ptr, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win.win_ptr, 3, 1L << 1, key_release, cub);
	mlx_loop_hook(cub->win.mlx, render, cub);
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
