#include "fdf.h"

static void	clear_fdf(t_fdf *fdf);

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
		ft_lstclear(&fdf->map, del);
		free(fdf);
	}
}
