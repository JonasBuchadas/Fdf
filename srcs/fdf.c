#include "fdf.h"

static void	init_fdf(t_fdf *fdf, char *filename);
static void	loop_fdf(t_fdf *fdf);

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = NULL;
	if (argc != 2)
		return (close_fdf(fdf, USAGE));
	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		return (close_fdf(fdf, MALLOC));
	init_fdf(fdf, argv[1]);
	loop_fdf(fdf);
	return (close_fdf(fdf, SUCCESS));
}

static void	init_fdf(t_fdf *fdf, char *filename)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		exit (close_fdf(fdf, MALLOC));
	fdf->fd = open(filename, O_RDONLY);
	if (fdf->fd < 0)
		exit (close_fdf(fdf, FD));
	fdf->filename = filename;
	read_map(fdf);
	fdf->win = mlx_new_window(fdf->mlx, W_WIDTH, W_HEIGHT, "FDF");
}

static void	loop_fdf(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, key_pressed, fdf);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
	mlx_loop(fdf->mlx);
}
