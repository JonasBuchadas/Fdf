#include "fdf.h"

void	draw_menu(t_fdf *fdf);

void	draw_img(t_fdf *fdf)
{
	draw_map(fdf);
	draw_menu(fdf);
}

void center_map(t_fdf *fdf)
{
	int	big_x;
	int	big_y;
	int	center_x;
	int	center_y;

    get_zrange(fdf);
	big_x = W_WIDTH - MENU_WIDTH;
	big_y = W_HEIGHT;
	center_x = 0;
	center_y = 0;
	if ((big_x / fdf->map_x / 2) > (big_y / fdf->map_y / 2))
		fdf->img->zoom = big_y / fdf->map_y / 2;
	else
		fdf->img->zoom = big_x / fdf->map_x / 2;
	if (fdf->img->zoom < 1)
		fdf->img->zoom = 1;
	center_x = (big_x / 2);
	center_y = (big_y / 2);
	fdf->img->map_start_x = center_x - ((fdf->map_x / 2) * fdf->img->zoom);
	fdf->img->map_start_y = center_y - ((fdf->map_y / 2) * fdf->img->zoom);
}

void get_zrange(t_fdf *fdf)
{
    t_image  *img;
    int     x;
    int     y;

    img = fdf->img;
    img->max_z = INT_MIN;
    img->min_z = INT_MAX;
    y = -1;
    while (++y < fdf->map_y)
    {
        x = -1;
        while (++x < fdf->map_x)
        {
	        if (img->max_z < fdf->map[y][x]->z)
                img->max_z = fdf->map[y][x]->z;
	        if (img->min_z > fdf->map[y][x]->z)
                img->min_z = fdf->map[y][x]->z;
        }       
    }
}

void	draw_menu(t_fdf *fdf)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = fdf->mlx;
	win = fdf->win;
	mlx_string_put(mlx, win, 50, y += 50, WHITE, "********************");
	mlx_string_put(mlx, win, 50, y += 20, WHITE, "* Fil de Fer (FDF) *");
	mlx_string_put(mlx, win, 50, y += 20, WHITE, "********************");
	mlx_string_put(mlx, win, 15, y += 70, WHITE, "Change Palette: C");
	mlx_string_put(mlx, win, 15, y += 50, WHITE, "Zoom: Scroll or +/-");
	mlx_string_put(mlx, win, 15, y += 30, WHITE, "Move: Arrow && Mouse");
	mlx_string_put(mlx, win, 15, y += 30, WHITE, "Elevation: U / D");
	mlx_string_put(mlx, win, 15, y += 60, WHITE, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, WHITE, "X-Axis - Key 4 or 6");
	mlx_string_put(mlx, win, 57, y += 25, WHITE, "Y-Axis - Key 2 or 8");
	mlx_string_put(mlx, win, 57, y += 25, WHITE, "Z-Axis - Key 1 or 9");
	mlx_string_put(mlx, win, 15, y += 50, WHITE, "Rotate Video: V");
}
