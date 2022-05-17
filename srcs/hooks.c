#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	exit(close_fdf(fdf, SUCCESS));
}

int	key_pressed(int key, t_fdf *fdf)
{
	if (key == ESC_KEY)
		exit(close_fdf(fdf, SUCCESS));
	return (0);
}
