/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:17:59 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 13:18:02 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "keys.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <errno.h>

// WINDOW SIZE
# define W_HEIGHT 800
# define W_WIDTH 1400
# define MENU_WIDTH 250

// ERROR CODES
# define SUCCESS 0
# define USAGE 1
# define MALLOC 2
# define FD 3
# define MAP 4
# define IMAGE 5

// COLORS
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define TEXT_COLOR 0xFF00FF
# define GREEN 0x03FC35
# define MAX_COLOR 0xA61206
# define POS_COLOR 0xE58C62
# define NEG_COLOR 0x3256A8

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
	bool	end;
	int		color;
}	t_coord;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		max_z;
	int		min_z;
	int		map_start_x;
	int		map_start_y;
	int		shift_x;
	int		shift_y;
	int		palette;
	int		projection;
	int		zoom;
	double	z_zoom;
	double	angle;
}				t_image;

typedef struct s_mouse
{
	int		previous_x;
	int		previous_y;
	bool	b_pressed;
	double	deg_value;
}	t_mouse;

typedef struct s_fdf {
	void	*mlx;
	void	*win;
	int		fd;
	int		map_x;
	int		map_y;
	char	*filename;
	t_coord	***map;
	t_image	*img;
}				t_fdf;

int		open_file(char *filename, t_fdf *fdf);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int		close_window(t_fdf *fdf);
int		close_fdf(t_fdf *fdf, int error_code);
int		key_press(int keycode, void *param);
void	show_menu(t_fdf *fdf);
void	read_map(t_fdf *fdf);
void	draw_img(t_fdf *fdf);
void	draw_map(t_fdf *fdf);
void	del(void *str);
float	float_module(float x);
float	max_float(float a, float b);
void	get_zrange(t_fdf *fdf);
void	center_map(t_fdf *fdf);

void	zoom(int keycode, t_fdf *fdf);
void	move(int keycode, t_fdf *fdf);
void	change_z(int keycode, t_fdf *fdf);
void	rotate(int keycode, t_fdf *fdf);
void	change_projection(int keycode, t_fdf *fdf);
void	reset_view(t_fdf *fdf);

#endif
