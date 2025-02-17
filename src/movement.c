
#include "cub.h"

static void	rotate_player(t_cub *cub, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

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

static void	move_forward_back(t_cub *cub, double move_speed, int direction)
{
	if (cub->data->map[(int)(cub->ray.pos_y)][(int)(cub->ray.pos_x
			+ cub->ray.dir_x * move_speed * direction)] != '1')
		cub->ray.pos_x += cub->ray.dir_x * move_speed * direction;
	if (cub->data->map[(int)(cub->ray.pos_y + cub->ray.dir_y
			* move_speed * direction)][(int)(cub->ray.pos_x)] != '1')
		cub->ray.pos_y += cub->ray.dir_y * move_speed * direction;
}

static void	move_left_right(t_cub *cub, double move_speed, int direction)
{
	if (cub->data->map[(int)(cub->ray.pos_y)][(int)(cub->ray.pos_x
			- cub->ray.dir_y * move_speed * direction)] != '1')
		cub->ray.pos_x -= cub->ray.dir_y * move_speed * direction;
	if (cub->data->map[(int)(cub->ray.pos_y + cub->ray.dir_x
			* move_speed * direction)][(int)(cub->ray.pos_x)] != '1')
		cub->ray.pos_y += cub->ray.dir_x * move_speed * direction;
}

void	move_player(t_cub *cub)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.045;
	rot_speed = 0.05;
	if (cub->keys.w)
		move_forward_back(cub, move_speed, 1);
	if (cub->keys.s)
		move_forward_back(cub, move_speed, -1);
	if (cub->keys.d)
		move_left_right(cub, move_speed, 1);
	if (cub->keys.a)
		move_left_right(cub, move_speed, -1);
	if (cub->keys.right)
		rotate_player(cub, -rot_speed);
	if (cub->keys.left)
		rotate_player(cub, rot_speed);
}

