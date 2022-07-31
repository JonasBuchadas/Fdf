#include "fdf.h"

static t_coord point_conversion(t_fdf *fdf, t_coord *point);
void draw_line(t_fdf *fdf, t_coord *start, t_coord *end);
void image_rotation(t_image *img, t_coord *point);

void draw_map(t_fdf *fdf)
{
    int x;
    int y;

    y = -1;
    while (++y < fdf->map_y)
    {
        x = -1;
        while (++x < fdf->map_x)
        {
            if (x < fdf->map_x -1)
                draw_line(fdf, fdf->map[y][x], fdf->map[y][x + 1]);
            if (y < fdf->map_y - 1)
                draw_line(fdf, fdf->map[y][x], fdf->map[y + 1][x]);
        }
    }
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
}

void draw_line(t_fdf *fdf, t_coord *start, t_coord *end)
{
    t_coord s;
    t_coord e;
    float   step_x;
    float   step_y;
    float   max;

    s = point_conversion(fdf, start);
    e = point_conversion(fdf, end);
    step_x = e.x - s.x;
    step_y = e.y - s.y;
    max = max_float(float_module(step_x), float_module(step_y));
    step_x /= max;
    step_y /= max;
    while((int) (s.x - e.x) || (int)(s.y - e.y))
    {
        my_mlx_pixel_put(fdf->img, s.x, s.y, 0x00FFFF00);
        s.x += step_x;
        s.y += step_y;
        if (s.x > W_WIDTH || s.y > W_HEIGHT || s.x < 0 || s.y < 0)
            break ;
    }
}

static t_coord point_conversion(t_fdf *fdf, t_coord *point)
{
    t_coord result;
//    double gradient;
    t_image *img;

    img = fdf->img;
//    gradient = get_gradient_color(img->min_z, img->max_z, point->z);
    result.x = point->x * img->zoom;
    result.y = point->y * img->zoom;
    result.z = point->z * img->zoom * img->z_zoom;
    result.special = point->special;
    image_rotation(fdf->img, &result);
    result.x += img->map_start_x + img->shift_x;
    result.y += img->map_start_y;
    return (result);
}
/*
static double get_gradient_color(int min, int max, int point)
{
    double total_distance;
    double point_distance;

    total_distance = max - min;
    point_distance = point - min;

    if (total_distance == 0)
        return (1.0);
    else
        return (point_distance / total_distance);
}
*/
void image_rotation(t_image *img, t_coord *point)
{
    double x;
    double y;
    double z;

    x = (double)point->x;
    y = (double)point->y;
    z = (double)point->z;
    point->x = (int)round((x - y) * cos(img->angle));
    point->y = (int)round((x + y) * sin(img->angle) - z);
}