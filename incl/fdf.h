#ifndef FDF_H
# define FDF_H

# include "keys.h"
# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define W_HEIGHT 800
# define W_WIDTH 800

// ERROR CODES
# define SUCCESS 0
# define USAGE 1
# define MALLOC 2
# define FD 3
# define MAP 4

typedef struct	s_fdf {
    void	*mlx;
    void	*win;
    int     fd;
    char    *filename;
	t_list	*map;
}				t_fdf;

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
}				t_data;

int 	open_file(char *filename, t_fdf *fdf);
int		close_window(t_fdf *fdf);
int 	close_fdf(t_fdf *fdf, int error_code);
int		key_pressed(int key, t_fdf *fdf);
void    read_map(t_fdf *fdf);
void    del(void *str);

#endif
