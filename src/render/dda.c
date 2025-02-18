/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:53:34 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/18 08:53:35 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	perform_dda(t_ray *ray, t_cub *cub)
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
	calculate_wall_dist(ray);
}

void	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
}

void	calculate_wall_height(t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
}
