#include "fdf.h"

void    del(void *str)
{
    char *line;

    line = (char *)str;
    ft_strdel(&line);
}

int	open_file(char *filename, t_fdf *fdf)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		close_fdf(fdf, FD);
	fdf->filename = filename;
	return (fd);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

float	float_module(float x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

float	max_float(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}