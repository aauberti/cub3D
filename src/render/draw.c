#include "cub.h"

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

static void	init_img_data(t_cub *cub, t_img_data *img_data)
{
	if (!cub || !cub->data || !cub->data->map || !cub->win.img)
		return ;
	img_data->addr = mlx_get_data_addr(cub->win.img, &img_data->bits_per_pixel,
			&img_data->line_length, &img_data->endian);
}

static void	draw_background(t_cub *cub, t_img_data *img_data)
{
	int	color_ceiling;
	int	color_floor;

	color_ceiling = (cub->data->c_color->r << 16) | (cub->data->c_color->g << 8)
		| cub->data->c_color->b;
	color_floor = (cub->data->f_color->r << 16) | (cub->data->f_color->g << 8)
		| cub->data->f_color->b;
	draw_section(img_data, 0, HEIGHT / 2, color_ceiling);
	draw_section(img_data, HEIGHT / 2, HEIGHT, color_floor);
}

static void	cast_single_ray(t_ray *ray, t_cub *cub, int x)
{
	calc_ray_pos(ray, x);
	init_dda(ray);
	perform_dda(ray, cub);
	calculate_wall_height(ray);
	draw_vertical_line(cub, x, ray->draw_start, ray->draw_end);
}

void	draw_walls(t_cub *cub)
{
	t_img_data	img_data;
	int			x;
	t_ray		*ray;

	init_img_data(cub, &img_data);
	if (!img_data.addr)
		return ;
	draw_background(cub, &img_data);
	ray = &cub->ray;
	x = 0;
	while (x < 1920)
	{
		cast_single_ray(ray, cub, x);
		x++;
	}
	mlx_put_image_to_window(cub->win.mlx, cub->win.win_ptr, cub->win.img, 0, 0);
}
