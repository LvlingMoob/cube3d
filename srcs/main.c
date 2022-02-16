#include "cube.h"

// int	render_next_frame(t_pos *pos)
// {
// 	mlx_clear_window(pos->vars->mlx, pos->vars->win);
// 	map_render(pos);
// 	if (pos->endgame)
// 		close_img_win(pos);
// 	return (1);
// }

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// int	close_img_win(t_vars *var)
// {
// 	mlx_destroy_window(var->mlx, var->win);
// 	exit(0);
// }

// int	key_hook(int key, t_vars *var)
// {
// 	if (key == 65307)
// 		close_img_win(var);
// 	return (0);
// }









void	initfdres(t_fd_read *fdres)
{
	fdres->values = ft_calloc(7, sizeof(char *));
	fdres->values[0] = ft_strdup("NO");
	fdres->values[1] = ft_strdup("SO");
	fdres->values[2] = ft_strdup("WE");
	fdres->values[3] = ft_strdup("EA");
	fdres->values[4] = ft_strdup("F");
	fdres->values[5] = ft_strdup("C");
	fdres->no = NULL;
	fdres->so = NULL;
	fdres->we = NULL;
	fdres->ea = NULL;
	fdres->f = NULL;
	fdres->c = NULL;
	fdres->map = NULL;
}

int	main(int argc, char **argv)
{
	t_fd_read	fdres;
	// t_data		img;
	// t_vars		var;

	if (argc != 2)
		return (1);
	initfdres(&fdres);
	file_handler(&fdres, argv[1]);
	free_and_quit(&fdres);

	// var.mlx = mlx_init();
	// var.win = mlx_new_window(var.mlx, 800, 600, "Cube3D");
	// img.img = mlx_new_image(var.mlx, 800, 600);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// mlx_key_hook(var.win, key_hook, &var);
	// // mlx_loop_hook(pos->vars->mlx, render_next_frame, pos);
	// mlx_hook(var.win, 17, 1L << 17, close_img_win, &var);
	// mlx_loop(var.mlx);
	return (0);
}
