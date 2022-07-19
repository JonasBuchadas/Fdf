#ifndef FDF_H
# define FDF_H

# include "keys.h"
# include "libft.h"
# include "mlx.h"
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
# define GREEN 0x03fc35
# define BACKGROUND 0x1A1A1D
# define MENU_BACKGROUND 0x950740

typedef struct s_coord
{
	int		x;
	int		y;
	int		z;
	bool	special;
	bool	end;
	int		color;
}	t_coord;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		max_z;
	int		min_z;
	int		map_start_x;
	int		map_start_y;
	int		palette;
	int		projection;
	int		zoom;
	double	z_zoom;

}				t_data;

typedef struct s_mouse
{
	int		previous_x;
	int		previous_y;
	bool	b_pressed;
	double	deg_value;
}	t_mouse;

typedef struct	s_fdf {
    void	*mlx;
    void	*win;
    int     fd;
	int		map_x;
	int		map_y;
    char    *filename;
	t_coord	***map;
	t_data	*img;
}				t_fdf;

int 	open_file(char *filename, t_fdf *fdf);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		close_window(t_fdf *fdf);
int 	close_fdf(t_fdf *fdf, int error_code);
int		key_pressed(int key, t_fdf *fdf);
void	show_menu(t_fdf *fdf);
void    read_map(t_fdf *fdf);
void 	draw_img(t_fdf *fdf);
void 	draw_map(t_fdf *fdf);
void    del(void *str);
void    get_zrange(t_fdf *fdf);
void    center_map(t_fdf *fdf);

#endif
