#include "cube.h"

// int	render_next_frame(t_pos *pos)
// {
// 	mlx_clear_window(pos->vars->mlx, pos->vars->win);
// 	map_render(pos);
// 	if (pos->endgame)
// 		close_img_win(pos);
// 	return (1);
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(/*int argc, char **argv*/)
{
	// t_fd_read	fdres;
	t_data		img;
	t_vars		var;

	// if (argc != 2)
	// 	return (1);
	// initfdres(&fdres);
	// parse_cub(&fdres, argv[1]);
	// free_and_quit(&fdres);

	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, 800, 600, "Cube3D");
	img.img = mlx_new_image(var.mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_key_hook(var.win, key_hook, &var);
	// mlx_loop_hook(pos->vars->mlx, render_next_frame, pos);
	mlx_hook(var.win, 17, 1L << 17, close_img_win, &var);
	mlx_loop(var.mlx);
	return (0);
}
