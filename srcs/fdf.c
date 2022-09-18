/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:47:44 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 16:05:36 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_fdf(t_fdf *fdf, char *filename);
static void	init_map(t_fdf *fdf, char *filename);
static void	count_lines(t_fdf *fdf);
static void	init_img(t_fdf *fdf);

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
	init_map(fdf, fdf->filename);
	read_map(fdf);
	init_img(fdf);
	draw_img(fdf);
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
	fdf->win = mlx_new_window(fdf->mlx, W_WIDTH, W_HEIGHT, filename);
	fdf->map_x = 0;
	fdf->map_y = 0;
}

static void	init_map(t_fdf *fdf, char *filename)
{
	count_lines(fdf);
	fdf->fd = open(filename, O_RDONLY);
	if (fdf->fd < 0)
		exit (close_fdf(fdf, FD));
	fdf->map = (t_coord ***)ft_calloc(fdf->map_y, sizeof(t_coord **));
	if (!fdf->map)
		exit(close_fdf(fdf, MALLOC));
	if (fdf->map_y == 0 || fdf->map_x == 0)
		exit(close_fdf(fdf, MAP));
}

static void	count_lines(t_fdf *fdf)
{
	char	*line;
	char	**points;

	while (1)
	{
		line = get_next_line(fdf->fd);
		if (!line)
			break ;
		points = ft_split(line, ' ');
		if (fdf->map_x == 0)
			fdf->map_x = ft_strarray_size(points);
		else if (fdf->map_x != ft_strarray_size(points))
		{
			ft_strdel(&line);
			ft_strarray_clear(&points);
			exit(close_fdf(fdf, MAP));
		}
		fdf->map_y++;
		ft_strdel(&line);
		ft_strarray_clear(&points);
	}
}

static void	init_img(t_fdf *fdf)
{
	t_image	*img;

	img = (t_image *)calloc(1, sizeof(t_image));
	if (!img)
		exit (close_fdf(fdf, MALLOC));
	fdf->img = img;
	img->img = mlx_new_image(fdf->mlx, W_WIDTH, W_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length,
			&img->endian);
	if (!img->img || !img->addr)
		exit(close_fdf(fdf, IMAGE));
	get_zrange(fdf);
	center_map(fdf);
	img->palette = 1;
	img->angle = 0.523599;
	img->projection = 1;
	img->z_zoom = 1;
	img->shift_x = W_WIDTH / 3;
	img->shift_y = W_HEIGHT / 10;
}
