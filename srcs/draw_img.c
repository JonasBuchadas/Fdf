/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:18:50 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 13:18:56 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_menu(t_fdf *fdf);
void	reset_img(t_fdf *fdf);

void	draw_img(t_fdf *fdf)
{
	reset_img(fdf);
	draw_map(fdf);
	draw_menu(fdf);
}

void	reset_img(t_fdf *fdf)
{
	int		*image;
	int		i;
	t_image	*img;

	img = fdf->img;
	ft_bzero(img->addr, W_WIDTH * W_HEIGHT * (img->bpp / 8));
	image = (int *)(img->addr);
	i = 0;
	while (i < W_HEIGHT * W_WIDTH)
	{
		if (i % W_WIDTH)
			image[i] = BLACK;
		i++;
	}
}

void	center_map(t_fdf *fdf)
{
	int	big_x;
	int	big_y;
	int	center_x;
	int	center_y;

	get_zrange(fdf);
	big_x = W_WIDTH - MENU_WIDTH;
	big_y = W_HEIGHT;
	center_x = 0;
	center_y = 0;
	if ((big_x / fdf->map_x / 2) > (big_y / fdf->map_y / 2))
		fdf->img->zoom = big_y / fdf->map_y / 2;
	else
		fdf->img->zoom = big_x / fdf->map_x / 2;
	if (fdf->img->zoom < 1)
		fdf->img->zoom = 1;
	center_x = (big_x / 2);
	center_y = (big_y / 2);
	fdf->img->map_start_x = center_x - ((fdf->map_x / 2) * fdf->img->zoom);
	fdf->img->map_start_y = center_y - ((fdf->map_y / 2) * fdf->img->zoom);
}

void	get_zrange(t_fdf *fdf)
{
	t_image	*img;
	int		x;
	int		y;

	img = fdf->img;
	img->max_z = INT_MIN;
	img->min_z = INT_MAX;
	y = -1;
	while (++y < fdf->map_y)
	{
		x = -1;
		while (++x < fdf->map_x)
		{
			if (img->max_z < fdf->map[y][x]->z)
				img->max_z = fdf->map[y][x]->z;
			if (img->min_z > fdf->map[y][x]->z)
				img->min_z = fdf->map[y][x]->z;
		}
	}
}

void	draw_menu(t_fdf *fdf)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = fdf->mlx;
	win = fdf->win;
	mlx_string_put(mlx, win, 50, y += 50, WHITE, "********************");
	mlx_string_put(mlx, win, 50, y += 20, WHITE, "* Fil de Fer (FDF) *");
	mlx_string_put(mlx, win, 50, y += 20, WHITE, "********************");
	mlx_string_put(mlx, win, 50, y += 50, WHITE, "Zoom In: +");
	mlx_string_put(mlx, win, 50, y += 50, WHITE, "Zoom Out: -");
	mlx_string_put(mlx, win, 50, y += 30, WHITE, "Move: Arrow Keys");
	mlx_string_put(mlx, win, 50, y += 30, WHITE, "Elevation: W / S");
	mlx_string_put(mlx, win, 50, y += 60, WHITE, "Rotate Up: A");
	mlx_string_put(mlx, win, 50, y += 30, WHITE, "Rotate Down: D");
	mlx_string_put(mlx, win, 50, y += 30, WHITE, "Isometric View On: 2");
	mlx_string_put(mlx, win, 50, y += 30, WHITE, "Isometric View Off: 1");
	mlx_string_put(mlx, win, 50, y += 30, WHITE, "Toggle Isometric View: Tab");
	mlx_string_put(mlx, win, 50, y += 30, WHITE, "Reset Configurations: R");
}
