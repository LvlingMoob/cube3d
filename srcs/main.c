/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:28:31 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 19:28:33 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int argc, char **argv)
{
	t_fd_read	fdres;
	t_data		img;
	t_vars		var;

	if (argc != 2)
		return (1);
	initfdres(&fdres);
	file_handler(&fdres, argv[1]);
	var.scale = 16;
	var_plyer_init(&var, &fdres, var.scale);

	int width = 64;
	int height = 64;

	free_and_quit(&fdres, 0);
	var.img = &img;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, S_WIDTH, S_HEIGHT, "Cube3D");
	img.img = mlx_new_image(var.mlx, S_WIDTH, S_HEIGHT);

	var.fool = mlx_xpm_file_to_image(var.mlx, "pics/hierophante.xpm", &width, &height);
	var.fd_no = (int *)mlx_get_data_addr(var.fool, &var.img->bits_per_pixel, &var.img->line_length, &var.img->endian);
	
	var.chariot = mlx_xpm_file_to_image(var.mlx, "pics/chariot.xpm", &width, &height);
	var.fd_we = (int *)mlx_get_data_addr(var.chariot, &var.img->bits_per_pixel, &var.img->line_length, &var.img->endian);
	
	var.hermit = mlx_xpm_file_to_image(var.mlx, "pics/hermit.xpm", &width, &height);
	var.fd_ea = (int *)mlx_get_data_addr(var.hermit, &var.img->bits_per_pixel, &var.img->line_length, &var.img->endian);

	var.world = mlx_xpm_file_to_image(var.mlx, "pics/world.xpm", &width, &height);
	var.fd_so = (int *)mlx_get_data_addr(var.world, &var.img->bits_per_pixel, &var.img->line_length, &var.img->endian);


	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	mlx_hook(var.win, 2, 1L << 0, key_press, &var);
	mlx_loop_hook(var.mlx, render_next_frame, &var);
	mlx_hook(var.win, 17, 1L << 17, close_img_win, &var);
	mlx_loop(var.mlx);
	return (0);
}
// mlx_hook(var.win, 3, 1L << 1, key_relase, &var);


// int width = 64;
// int height = 64;
// int	*ret;
// void *test = mlx_xpm_file_to_image(var.mlx, argv[1], &width, &height);

// ret = ft_calloc(1, sizeof(int));
// ret = (int *)mlx_get_data_addr(test, &img.bits_per_pixel, &img.line_length, &img.endian);
// while (*ret)
// 	printf("%d\n", *(ret++));