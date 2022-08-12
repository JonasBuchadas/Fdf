#include "fdf.h"

static void		parse_line(t_fdf *fdf, char *line, int y);
static t_coord	*parse_point(t_fdf *fdf, char *point, int x, int y);

void	read_map(t_fdf *fdf)
{
	char	*line;
	int		y;

	y = 0;
	while (1)
	{
		line = get_next_line(fdf->fd);
		if (!line)
			break ;
		parse_line(fdf, line, y);
		ft_strdel(&line);
		y++;
	}
}

static void	parse_line(t_fdf *fdf, char *line, int y)
{
	int		x;
	char	**points;
	t_coord	**coords;

	points = ft_split(line, ' ');
	if (!points)
		exit(close_fdf(fdf, MALLOC));
	coords = (t_coord **)ft_calloc(fdf->map_x, sizeof(t_coord *));
	if (!coords)
		exit(close_fdf(fdf, MALLOC));
	x = -1;
	while (++x < fdf->map_x)
		coords[x] = parse_point(fdf, points[x], x, y);
	fdf->map[y] = coords;
	ft_strarray_clear(&points);
}

static t_coord	*parse_point(t_fdf *fdf, char *point, int x, int y)
{
	t_coord	*coord;

	coord = (t_coord *)ft_calloc(1, sizeof(t_coord));
	if (!coord)
		exit(close_fdf(fdf, MALLOC));
	coord->x = x;
	coord->y = y;
	coord->z = ft_atoi(point);
	return (coord);
}
