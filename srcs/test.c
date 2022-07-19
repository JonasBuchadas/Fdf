#include "fdf.h"
#include <stdio.h>

int	exit_win(t_fdf *vars);

int minimize()
{
    printf("Hello\n");
    return (0);
}

int	exit_win(t_fdf *vars)
{
	if (vars)
		mlx_destroy_window(vars->mlx, vars->win);
	exit (0);
}

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

unsigned char	get_tr(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}

int oposite_color(int color)
{
	unsigned char t;
	int	r;
	int g;
	int b;

	t = get_tr(color);
	r = (int)get_r(color);
	g = (int)get_g(color);
	b = (int)get_b(color);
	r = (r * -1) + 255;
	g = (g * -1) + 255;
	b = (b * -1) + 255;
	return (create_trgb(t, (unsigned char)r, (unsigned char)g, (unsigned char)b));
}

int	main(void)
{
	t_fdf	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 600, 600, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, key_pressed, &vars);
	mlx_hook(vars.win, 17, 0, exit_win, &vars);
    mlx_hook(vars.win, 6, 1L<<4, minimize, &vars);
	mlx_loop(vars.mlx);

}