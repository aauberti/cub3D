/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:53:14 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/18 08:53:15 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
