#include "cub.h"

static void    init_dda(t_ray *ray)
{
    if (!ray)
        return ;
    ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);
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

static void perform_dda(t_ray *ray, t_cub *cub)
{
    int hit;

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
        ray->perp_wall_dist = (ray->map_x - ray->pos_x + 
            (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - ray->pos_y + 
            (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

static void calculate_wall_height(t_ray *ray)
{
    ray->line_height = (int)(1080 / ray->perp_wall_dist);
    ray->draw_start = -ray->line_height / 2 + 1080 / 2;
    ray->draw_end = ray->line_height / 2 + 1080 / 2;

    if (ray->draw_start < 0)
        ray->draw_start = 0;
    if (ray->draw_end >= 1080)
        ray->draw_end = 1080 - 1;
}

static void init_player_dir(t_ray *ray, char dir)
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

void find_player_pos(t_cub *cub)
{
    int y;
    int x;
    
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
                return;
            }
            x++;
        }
        y++;
    }
}

static void draw_vertical_line(t_cub *cub, int x, int start, int end)
{
    int     y;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     color;

    if (!cub || !cub->win.img)
        return ;
    addr = mlx_get_data_addr(cub->win.img, &bits_per_pixel, &line_length, &endian);
    if (!addr)
        return ;
    color = (cub->ray.side == 1) ? 0x00FFFFFF : 0x00CCCCCC;
    y = start;
    while (y < end && y < 1080)
    {
        if (y >= 0)
        {
            int pixel = y * line_length + x * (bits_per_pixel / 8);
            addr[pixel] = color & 0xFF;
            addr[pixel + 1] = (color >> 8) & 0xFF;
            addr[pixel + 2] = (color >> 16) & 0xFF;
        }
        y++;
    }
}

void    draw_walls(t_cub *cub)
{
    int     x;
    t_ray   *ray;

    if (!cub || !cub->data || !cub->data->map)
        return ;
    ray = &cub->ray;
    if (!ray)
        return ;
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
