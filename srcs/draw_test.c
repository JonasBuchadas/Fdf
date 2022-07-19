#include "fdf.h"

float	fmodule(float i)
{
	return (i < 0) ? -i : i;
}

void	line(t_coord *a, t_coord *b, t_fdf *fdf)
{
	float	step_x;
	float	step_y;
	float	max;
	int		color;

	set_param(&a, &b, fdf);
	step_x = b->x - a->x;
	step_y = b->y - a->y;
	max = MAX(fmodule(step_x), fmodule(step_y));
	step_x /= max;
	step_y /= max;
	color = (b->z || a->z) ? 0xfc0345 : 0xBBFAFF;
	color = (b->z != a->z) ? 0xfc031c : color;
	while ((int)(a->x - b->x) || (int)(a->y - b->y))
	{
		mlx_pixel_put(fdf->mlx, fdf->win, a->x, a->y, color);
		a->x += step_x;
		a->y += step_y;
		if (a->x > fdf->map_x || a->y > fdf->map_y || a->y < 0 || a->x < 0)
			break ;
	}
}

void	draw(t_fdf *fdf, t_coord ***map)
{
	int		y;
	int		x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (1)
		{
			if (map[y + 1])
				line(map[y][x], map[y + 1][x], fdf);
			if (!map[y][x]->end)
				line(map[y][x], map[y][x + 1], fdf);
			if (map[y][x]->end)
				break ;
			x++;
		}
		y++;
	}
}