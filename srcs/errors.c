/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:19:02 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 14:11:26 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	//	if (fdf->img)
		{
			mlx_destroy_image(fdf->mlx, fdf->img->img);
			free(fdf->img);
		}
		if (fdf->win)
			mlx_destroy_window(fdf->mlx, fdf->win);
		if (fdf->mlx)
			free(fdf->mlx);
		if (fdf->map)
			clear_map(fdf);
		if (fdf)
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
			free(fdf->map[y][x]);
		//	ft_memdel((void **)&fdf->map[y][x]);
		free(fdf->map[y]);
		//ft_memdel((void **)&fdf->map[y]);
	}
	free(fdf->map);
}
