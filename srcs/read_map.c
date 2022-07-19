#include "fdf.h"

static void		parse_line(t_fdf *fdf, char *line, int y);
static t_coord	*parse_point(t_fdf *fdf, char *point, int x, int y);
static void		check_int(t_fdf *fdf, char *s);

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
	if (fdf->map_x != ft_strarray_size(points))
		exit(close_fdf(fdf, MAP));
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
	char	**point_info;

	point_info = ft_split(point, ',');
	if (!point_info)
		exit(close_fdf(fdf, MALLOC));
	coord = (t_coord *)ft_calloc(1, sizeof(t_coord));
	check_int(fdf, point_info[0]);
	coord->x = x;
	coord->y = y;
	coord->z = ft_atoi(point_info[0]);
	if (point_info[1])
	{
		coord->special = true;
		coord->color = ft_atoi_base(point_info[1], 16);
	}
	if (ft_strchr(point, '\n'))
		coord->end = true;
	return (coord);
}

static void	check_int(t_fdf *fdf, char *s)
{
	int	n;
	int	i;

	i = -1;
	if (s[0] == '-' && ft_isdigit(s[1]) == 1)
		i++;
	while (s[++i] && s[i] != '\n')
	{
		if (ft_isdigit(s[i]) == 0)
			exit(close_fdf(fdf, MAP));
	}		
	n = ft_atoi((const char *)s);
	if (n == 0 && ft_strncmp(s, "0", 1) != 0)
		exit(close_fdf(fdf, MAP));
}
