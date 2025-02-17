#include "cub.h"

void	setup_hooks(t_cub *cub)
{
	mlx_hook(cub->win.win_ptr, 17, 0, close_window, cub);
	mlx_hook(cub->win.win_ptr, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win.win_ptr, 3, 1L << 1, key_release, cub);
	mlx_loop_hook(cub->win.mlx, render, cub);
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
