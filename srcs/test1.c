#include "fdf.h"

static void	draw_line(t_image img);

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_image	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 800, "Hello world!");
	img.img = mlx_new_image(mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	draw_line(img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

static void	draw_line(t_image img)
{
	int start[2] = {40, 100}; 
	int end[2] = {100, -40};
	float step_x;
	float step_y;
	float max;

	step_x = end[0] - start[0];
	step_y = end[1] - start[1];
	max = 140;
	step_x /= max;
	step_y /= max;
	while ((int)(start[0] - end[0]) || (int)(start[1] - end[1]))
	{
		my_mlx_pixel_put(&img, start[0], start[1], 0x00FFFF00);
		start[0] += step_x;
		start[1] += step_y;
		if (start[0] < 0 || start[1] < 0)
			break;
	}	
}