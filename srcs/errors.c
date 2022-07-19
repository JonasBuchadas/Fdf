#include "fdf.h"

static void	clear_fdf(t_fdf *fdf);
static void	clear_map(t_fdf *fdf);

int	close_fdf(t_fdf *fdf, int error_code)
{
	if (error_code == USAGE)
		ft_putendl_fd("USAGE: ./fdf [map.fdf]", STDERR_FILENO);
	else if (error_code == MALLOC)
		ft_putendl_fd("MALLOC ERROR", STDERR_FILENO);
	else if (error_code == FD)
		ft_putendl_fd("FILE NOT FOUND", STDERR_FILENO);
	else if (error_code == MAP)
		ft_putendl_fd("INCORRECT VALUE IN MAP", STDERR_FILENO);
	else if (error_code == IMAGE)
		ft_putendl_fd("FAILURE TO INITIALIZE IMAGE", STDERR_FILENO);
	clear_fdf(fdf);
	return (error_code);
}

static void	clear_fdf(t_fdf *fdf)
{
	if (fdf)
	{
		if (fdf->win)
			mlx_destroy_window(fdf->mlx, fdf->win);
		if (fdf->mlx)
			free(fdf->mlx);
		if (fdf->map)
			clear_map(fdf);
		if (fdf->img)
			free(fdf->img);
		free(fdf);
	}
}

static void	clear_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < fdf->map_y)
	{
		x = -1;
		while (++x < fdf->map_x)
		{
			ft_memdel((void **)&fdf->map[y][x]);
		}
	}
	free(fdf->map);
}
