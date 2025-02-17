#include "cub.h"

void	*get_texture(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (cub->img.west);
		else
			return (cub->img.east);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (cub->img.north);
		else
			return (cub->img.south);
	}
}

void	calc_texture_x(t_ray *ray, double *wall_x, int *tex_x)
{
	if (ray->side == 0)
		*wall_x = ray->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		*wall_x = ray->pos_x + ray->wall_dist * ray->ray_dir_x;
	*wall_x = *wall_x - floor(*wall_x);
	*tex_x = (int)(*wall_x * 64);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		*tex_x = 64 - *tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		*tex_x = 64 - *tex_x - 1;
}
