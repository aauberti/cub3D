#include "cub.h"

static void	init_dda(t_ray *ray)
{
	if (!ray)
		return ;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_cub *cub)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub->data->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
}

static void	calculate_wall_height(t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
}

static void	init_player_dir(t_ray *ray, char dir)
{
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0;
	if (dir == 'N')
	{
		ray->dir_y = -1;
		ray->plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		ray->dir_y = 1;
		ray->plane_x = -0.66;
	}
	else if (dir == 'E')
	{
		ray->dir_x = 1;
		ray->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		ray->dir_x = -1;
		ray->plane_y = -0.66;
	}
}

void	find_player_pos(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (cub->data->map[y])
	{
		x = 0;
		while (cub->data->map[y][x])
		{
			if (ft_strchr("NSEW", cub->data->map[y][x]))
			{
				cub->ray.pos_x = x + 0.5;
				cub->ray.pos_y = y + 0.5;
				init_player_dir(&cub->ray, cub->data->map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	draw_vertical_line(t_cub *cub, int x, int start, int end)
{
	void	*texture;
	char	*tex_addr;
	int		tex_bpp;
	int		tex_line_len;
	int		tex_endian;
	double	wall_x;
	int		tex_x;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		pixel;
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		tex_pixel;
	int		color;

	if (cub->ray.side == 0)
	{
		if (cub->ray.ray_dir_x > 0)
			texture = cub->img.west;
		else
			texture = cub->img.east;
	}
	else
	{
		if (cub->ray.ray_dir_y > 0)
			texture = cub->img.north;
		else
			texture = cub->img.south;
	}
	if (cub->ray.side == 0)
		wall_x = cub->ray.pos_y + cub->ray.wall_dist * cub->ray.ray_dir_y;
	else
		wall_x = cub->ray.pos_x + cub->ray.wall_dist * cub->ray.ray_dir_x;
	wall_x = wall_x - floor(wall_x);
	tex_x = (int)(wall_x * 64);
	if (cub->ray.side == 0 && cub->ray.ray_dir_x > 0)
		tex_x = 64 - tex_x - 1;
	if (cub->ray.side == 1 && cub->ray.ray_dir_y < 0)
		tex_x = 64 - tex_x - 1;
	tex_addr = mlx_get_data_addr(texture, &tex_bpp, &tex_line_len, &tex_endian);
	addr = mlx_get_data_addr(cub->win.img, &bpp, &line_len, &endian);
		step = (double)64 / cub->ray.line_height;
		tex_pos = (start - HEIGHT / 2 + cub->ray.line_height / 2) * step;
	// if (cub->ray.line_height > HEIGHT)
	// {
	// 	step = (double)64 / cub->ray.line_height;
	// 	tex_pos = (start - HEIGHT / 2 + cub->ray.line_height / 2) * step;
	// }
	// else
	// {
	// 	step = (double)64 / (end - start);
	// 	tex_pos = 0;
	// }
	y = start;
	while (y < end && y < HEIGHT)
	{
		if (y >= 0)
		{
			tex_y = (int)tex_pos & 63;
			tex_pos += step;
			tex_pixel = tex_y * tex_line_len + tex_x * (tex_bpp / 8);
			color = *(int *)(tex_addr + tex_pixel);
			if (cub->ray.side == 1)
				color = (color >> 1) & 8355711;
			pixel = y * line_len + x * (bpp / 8);
			addr[pixel] = color & 0xFF;
			addr[pixel + 1] = (color >> 8) & 0xFF;
			addr[pixel + 2] = (color >> 16) & 0xFF;
		}
		y++;
	}
}

void	draw_walls(t_cub *cub)
{
	t_img_data	img_data;
	int			x;
	t_ray		*ray;
	int			color_ceiling;
	int			color_floor;

	if (!cub || !cub->data || !cub->data->map || !cub->win.img)
		return ;
	img_data.addr = mlx_get_data_addr(cub->win.img, &img_data.bits_per_pixel,
			&img_data.line_length, &img_data.endian);
	color_ceiling = (cub->data->c_color->r << 16) | (cub->data->c_color->g << 8) | cub->data->c_color->b;
	color_floor = (cub->data->f_color->r << 16) | (cub->data->f_color->g << 8) | cub->data->f_color->b;
	draw_section(&img_data, 0, HEIGHT / 2, color_ceiling);
	draw_section(&img_data, HEIGHT / 2, HEIGHT, color_floor);
	ray = &cub->ray;
	x = 0;
	while (x < 1920)
	{
		ray->camera_x = 2 * x / (double)1920 - 1;
		ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
		init_dda(ray);
		perform_dda(ray, cub);
		calculate_wall_height(ray);
		draw_vertical_line(cub, x, ray->draw_start, ray->draw_end);
		x++;
	}
	mlx_put_image_to_window(cub->win.mlx, cub->win.win_ptr, cub->win.img, 0, 0);
}
