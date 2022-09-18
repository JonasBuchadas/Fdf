/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:18:15 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 13:18:17 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	exit(close_fdf(fdf, SUCCESS));
}

int	key_press(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == ESC_KEY)
		exit(close_fdf(fdf, SUCCESS));
	else if (keycode == MINUS_KEY || keycode == PLUS_KEY)
		zoom(keycode, fdf);
	else if (keycode == LEFT_KEY || keycode == RIGHT_KEY \
			|| keycode == UP_KEY || keycode == DOWN_KEY)
		move(keycode, fdf);
	else if (keycode == W_KEY || keycode == S_KEY)
		change_z(keycode, fdf);
	else if (keycode == A_KEY || keycode == D_KEY)
		rotate(keycode, fdf);
	else if (keycode == TAB_KEY || keycode == ONE_KEY || keycode == TWO_KEY)
		change_projection(keycode, fdf);
	else if (keycode == R_KEY)
		reset_view(fdf);
	return (0);
}

void	reset_view(t_fdf *fdf)
{
	t_image	*img;

	img = fdf->img;
	get_zrange(fdf);
	center_map(fdf);
	img->palette = 1;
	img->angle = 0.523599;
	img->projection = 1;
	img->z_zoom = 1;
	img->shift_x = W_WIDTH / 3;
	img->shift_y = W_HEIGHT / 10;
	draw_img(fdf);
}
