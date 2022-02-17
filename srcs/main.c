#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw(t_vars *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var->map[i])
	{
		j = 0;
		while (var->map[i][j])
		{
			if (var->map[i][j] == 'N')
				break;
			j++;
		}
		i++;
	}
	for (int k = 0; k < 64; k++)
	{
		for (int l = 0; l < 64; l++)
		{
			my_mlx_pixel_put(var->img, var->plyer->x + k, var->plyer->y + l, 0x00FF0000);
		}
	}
}

void	home_clear_window(t_vars *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 800)
	{
		j = 0;
		while (j < 600)
		{
			
			j++;
		}
		i++;
	}
}

int	render_next_frame(t_vars *var)
{
	//home_clear_window(var);

	for (int i = 0; i < 800; i++)
	{
		for (int j = 0; j < 600; j++)
			my_mlx_pixel_put(var->img, i, j, 0x00000000);
	}
	my_mlx_pixel_put(var->img, var->plyer->x, var->plyer->y, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->x + 1, var->plyer->y, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->x + 1, var->plyer->y + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->x + 1, var->plyer->y - 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->x - 1, var->plyer->y, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->x - 1, var->plyer->y + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->x - 1, var->plyer->y - 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->x, var->plyer->y + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->x, var->plyer->y - 1, 0x00FFFFFF);
	

	mlx_put_image_to_window(var->mlx, var->win, var->img->img, 0, 0);

	return (1);
}

int	close_img_win(t_vars *var)
{
	mlx_destroy_image(var->mlx, var->img->img);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	free_var(var);
	exit(0);
}

int	key_press(int key, t_vars *var)
{
	if (key == 65307)
		close_img_win(var);
	else if (key == 122) // UP
		var->plyer->y--;
	else if (key == 113) // LEFT
		var->plyer->x--;
	else if (key == 100) // RIGHT
		var->plyer->x++;
	else if (key == 115) // DOWN
		var->plyer->y++;
	return (0);
}


// int	key_relase(int key, t_vars *var)
// {

// 	// if (key == 65307)
// 	// 	close_img_win(var);
// 	// else if (key == 122) // UP
// 	// 	var->plyer->y--;
// 	// else if (key == 113) // LEFT
// 	// 	var->plyer->x--;
// 	// else if (key == 100) // RIGHT
// 	// 	var->plyer->x++;
// 	// else if (key == 115) // DOWN
// 	// 	var->plyer->y++;
// 	// return (0);
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

void	var_plyer_init(t_vars *var, t_fd_read *fdres)
{
	int	i;
	int	j;

	i = 0;
	cp_char_array(&var->map, fdres->map);
	while (var->map[i])
	{
		j = 0;
		while (var->map[i][j])
		{
			if (var->map[i][j] == 'N' || var->map[i][j] == 'S' || var->map[i][j] == 'W' || var->map[i][j] == 'E')
				break ;
			j++;
		}
		i++;
	}
	var->plyer = ft_calloc(1, sizeof(t_plyer));
	var->plyer->x = i;
	var->plyer->y = j;
	// if (var->map[i][j] == 'N')
	// 	var->plyer->orientation = 0;
	// else if (var->map[i][j] == 'S')
	// 	var->plyer->orientation = 1/2pi;
	// else if (var->map[i][j] == 'W')
	// 	var->plyer->orientation = pi;
	// else if (var->map[i][j] == 'E')
	// 	var->plyer->orientation = 3/2pi;
}

int	main(int argc, char **argv)
{
	t_fd_read	fdres;
	t_data		img;
	t_vars		var;

	if (argc != 2)
		return (1);
	initfdres(&fdres);
	file_handler(&fdres, argv[1]);
	var_plyer_init(&var, &fdres);
	free_and_stay(&fdres);

	var.img = &img;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, 800, 600, "Cube3D");
	img.img = mlx_new_image(var.mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// mlx_key_hook(var.win, key_hook, &var);
	mlx_hook(var.win, 2, 1L << 0, key_press, &var);
	// mlx_hook(var.win, 3, 1L << 1, key_relase, &var);
	mlx_loop_hook(var.mlx, render_next_frame, &var);
	mlx_hook(var.win, 17, 1L << 17, close_img_win, &var);
	mlx_loop(var.mlx);
	return (0);
}
