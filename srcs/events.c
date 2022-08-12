#include "fdf.h"

void	zoom(int keycode, t_fdf *fdf)
{
	if (keycode == PLUS_KEY)
		fdf->img->zoom += 1;
	else if (keycode == MINUS_KEY)
		fdf->img->zoom -= 1;
	if (fdf->img->zoom < 1)
		fdf->img->zoom = 1;
	draw_img(fdf);
}

void	move(int keycode, t_fdf *fdf)
{
	if (keycode == UP_KEY)
		fdf->img->shift_y -= 10;
	else if (keycode == DOWN_KEY)
		fdf->img->shift_y += 10;
	else if (keycode == LEFT_KEY)
		fdf->img->shift_x -= 10;
	else if (keycode == RIGHT_KEY)
		fdf->img->shift_x += 10;
	draw_img(fdf);
}

void	change_z(int keycode, t_fdf *fdf)
{
	if (keycode == W_KEY)
		fdf->img->z_zoom += 0.1;
	else if (keycode == S_KEY)
		fdf->img->z_zoom -= 0.1;
	draw_img(fdf);
}

void	rotate(int keycode, t_fdf *fdf)
{
	if (keycode == A_KEY)
		fdf->img->angle += 0.05;
	else if (keycode == D_KEY)
		fdf->img->angle -= 0.05;
	draw_img(fdf);
}

void	change_projection(int keycode, t_fdf *fdf)
{
	if (keycode == TAB_KEY)
	{
		if (fdf->img->projection == 0)
			fdf->img->projection = 1;
		else
			fdf->img->projection = 0;
	}
	else if (keycode == ONE_KEY)
		fdf->img->projection = 0;
	else if (keycode == TWO_KEY)
		fdf->img->projection = 1;
	draw_img(fdf);
}
