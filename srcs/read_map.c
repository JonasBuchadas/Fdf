#include "fdf.h"

static void parse_line(t_fdf *fdf, char *line);
static void check_int(t_fdf *fdf, char *s);

void    read_map(t_fdf *fdf)
{
    char    *line;

    fdf->map = NULL;
    while (1) 
    {
        line = get_next_line(fdf->fd);
        if (!line)
            break ;
        parse_line(fdf, line);
        ft_strdel(&line);
    }
//  ft_lstiter(fdf->map, print);
}

static void parse_line(t_fdf *fdf, char *line)
{
    int     i;
    char    **points;

    points = ft_split(line, ' ');
    if (!points)
        exit(close_fdf(fdf, MALLOC));
    i = -1;
    while (ft_strarray_size(points) > ++i)
        check_int(fdf, points[i]);
    ft_lstadd_back(&fdf->map, ft_lstnew((void *)ft_strdup(line)));
    ft_strarray_clear(&points);
}
static void check_int(t_fdf *fdf, char *s)
{
    int n;
    int i;

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