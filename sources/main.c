#include "cub.h"

void free_images(t_cub *cub)
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

int end(t_cub *cub)
{
	free_images(cub);
	free_data(cub->data);
	mlx_destroy_window(cub->win.mlx, cub->win.win_ptr);
	mlx_destroy_display(cub->win.mlx);
	free(cub->win.mlx);
	free(cub);
	exit(0);
}

bool init_img(t_cub *cub)
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

static bool init_background(t_cub *cub, t_img_data *img_data)
{
    cub->win.img = mlx_new_image(cub->win.mlx, 1920, 1080);
    if (!cub->win.img)
        return (false);
    img_data->addr = mlx_get_data_addr(cub->win.img, 
        &img_data->bits_per_pixel,
        &img_data->line_length,
        &img_data->endian);
    return (img_data->addr != NULL);
}

static void draw_section(t_img_data *img_data, int y_start, int y_end, int color)
{
    int x;
    int y;
    int pixel;

    y = y_start;
    while (y < y_end)
    {
        x = 0;
        while (x < 1920)
        {
            pixel = y * img_data->line_length + x * (img_data->bits_per_pixel / 8);
            img_data->addr[pixel] = color & 0xFF;
            img_data->addr[pixel + 1] = (color >> 8) & 0xFF;
            img_data->addr[pixel + 2] = (color >> 16) & 0xFF;
            x++;
        }
        y++;
    }
}

void draw_background(t_cub *cub)
{
    t_img_data   img_data;
    int         color_ceiling;
    int         color_floor;

    color_ceiling = (cub->data->c_color->r << 16) | 
                   (cub->data->c_color->g << 8) | 
                   cub->data->c_color->b;
    color_floor = (cub->data->f_color->r << 16) | 
                  (cub->data->f_color->g << 8) | 
                  cub->data->f_color->b;

    if (!init_background(cub, &img_data))
        return ;
    draw_section(&img_data, 0, 1080 / 2, color_ceiling);
    draw_section(&img_data, 1080 / 2, 1080, color_floor);
    mlx_put_image_to_window(cub->win.mlx, cub->win.win_ptr, cub->win.img, 0, 0);
}

void error_path(t_cub *cub)
{
	free_images(cub);
	free_data(cub->data);
	mlx_destroy_display(cub->win.mlx);
	free(cub->win.mlx);
	free(cub);
	exit(0);
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
	ft_memset(&cub->img, 0, sizeof(t_img));
	if (!init_img(cub))
		return (error_path(cub));
	if (!cub->win.mlx)
		return (free(cub));
	cub->win.win_ptr = mlx_new_window(cub->win.mlx, 1920, 1080, "cub3D");
	find_player_pos(cub);
    draw_background(cub);
    draw_walls(cub);
	mlx_hook(cub->win.win_ptr, 17, 4, end, cub);
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
