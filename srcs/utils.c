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
