#include "fdf.h"

void	show_menu(t_fdf *fdf)
{
	char *menu;

	menu = "up, down, left, right: move picture";
	mlx_string_put(fdf->mlx, fdf->win, 10, 15, GREEN, menu);
	menu = "5, space: 3d/2d mode; +, -: zoom";
	mlx_string_put(fdf->mlx, fdf->win, 10, 30, GREEN, menu);
	menu = "8, 2: z-scale; 4, 6: rotation";
	mlx_string_put(fdf->mlx, fdf->win, 10, 45, GREEN, menu);
	menu = "f: full screen mode";
	mlx_string_put(fdf->mlx, fdf->win, 10, 60, GREEN, menu);
}