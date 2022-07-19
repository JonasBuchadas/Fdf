#include "fdf.h"

void	draw_menu(t_fdf *fdf);
void	draw_menu_background(t_data *img);

void	draw_img(t_fdf *fdf)
{
	draw_menu_background(fdf->img);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
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
	center_x = (big_x / 2) + MENU_WIDTH;
	center_y = (big_y / 2);
	fdf->img->map_start_x = center_x - ((fdf->map_x / 2) * fdf->img->zoom);
	fdf->img->map_start_y = center_y - ((fdf->map_y / 2) * fdf->img->zoom);
}

void get_zrange(t_fdf *fdf)
{
    t_data  *img;
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
	mlx_string_put(mlx, win, 50, y += 20, WHITE, "********************");
	mlx_string_put(mlx, win, 50, y += 20, WHITE, "* Fil de Fer (FDF) *");
	mlx_string_put(mlx, win, 50, y += 20, WHITE, "********************");
	mlx_string_put(mlx, win, 15, y += 70, TEXT_COLOR, "Change Palette: C");
	mlx_string_put(mlx, win, 15, y += 50, TEXT_COLOR, "Zoom: Scroll or +/-");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Move: Arrow && Mouse");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Elevation: U / D");
	mlx_string_put(mlx, win, 15, y += 60, WHITE, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "X-Axis - Key 4 or 6");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Y-Axis - Key 2 or 8");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Z-Axis - Key 1 or 9");
//	projection_menu_selector(fdf, mlx, win, y);
	mlx_string_put(mlx, win, 15, y += 200, TEXT_COLOR, "Rotate Video: V");
}

void	draw_menu_background(t_data *img)
{
	size_t	offset;
	char	*pixel;
	size_t	x;
	size_t	y;

	y = -1;
	ft_bzero(img->addr, W_WIDTH * W_HEIGHT * (img->bits_per_pixel / 8));
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < MENU_WIDTH)
		{
			offset = (y * img->line_length) + x * (img->bits_per_pixel / 8);
			pixel = img->addr + offset;
			*(unsigned int *)pixel = MENU_BACKGROUND;
		}
	}
}
