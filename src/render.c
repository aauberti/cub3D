/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:53:11 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/18 08:53:12 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_player_dir(t_ray *ray, char dir)
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
