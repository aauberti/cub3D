#include "cub.h"

static void	init_line_vars(t_line_vars *vars, t_cub *cub, int x, t_ray *ray)
{
	vars->texture = get_texture(cub, ray);
	vars->tex_addr = mlx_get_data_addr(vars->texture, &vars->tex_bpp,
			&vars->tex_line_len, &vars->tex_endian);
	vars->addr = mlx_get_data_addr(cub->win.img, &vars->bpp,
			&vars->line_len, &vars->endian);
	calc_texture_x(ray, &vars->wall_x, &vars->tex_x);
	vars->step = (double)64 / ray->line_height;
	vars->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* vars->step;
	vars->x = x;
}

static void	put_pixel(t_line_vars *vars, int y, int color)
{
	int	pixel;

	pixel = y * vars->line_len + vars->x * (vars->bpp / 8);
	vars->addr[pixel] = color & 0xFF;
	vars->addr[pixel + 1] = (color >> 8) & 0xFF;
	vars->addr[pixel + 2] = (color >> 16) & 0xFF;
}

void	draw_vertical_line(t_cub *cub, int x, int start, int end)
{
	t_line_vars	vars;
	int			y;
	int			tex_y;
	int			tex_pixel;
	int			color;

	init_line_vars(&vars, cub, x, &cub->ray);
	y = start;
	while (y < end && y < HEIGHT)
	{
		if (y >= 0)
		{
			tex_y = (int)vars.tex_pos & 63;
			vars.tex_pos += vars.step;
			tex_pixel = tex_y * vars.tex_line_len + vars.tex_x
				* (vars.tex_bpp / 8);
			color = *(int *)(vars.tex_addr + tex_pixel);
			if (cub->ray.side == 1)
				color = (color >> 1) & 8355711;
			put_pixel(&vars, y, color);
		}
		y++;
	}
}
