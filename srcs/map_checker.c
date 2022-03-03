/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:28:48 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 19:28:49 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	get_textures(t_vars *var)
{
	int	width;
	int	height;

	width = 64;
	height = 64;
	var->hiero = mlx_xpm_file_to_image(var->mlx, "pics/hierophante.xpm",
			&width, &height);
	var->fd_no = (int *)mlx_get_data_addr(var->hiero, &var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
	var->chariot = mlx_xpm_file_to_image(var->mlx, "pics/chariot.xpm",
			&width, &height);
	var->fd_we = (int *)mlx_get_data_addr(var->chariot,
			&var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
	var->hermit = mlx_xpm_file_to_image(var->mlx, "pics/hermit.xpm",
			&width, &height);
	var->fd_ea = (int *)mlx_get_data_addr(var->hermit,
			&var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
	var->world = mlx_xpm_file_to_image(var->mlx, "pics/world.xpm",
			&width, &height);
	var->fd_so = (int *)mlx_get_data_addr(var->world,
			&var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
}

void	map_checker(t_fd_read *fdres)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (fdres->map[i])
	{
		j = 0;
		first_carac_checker(fdres, i);
		if (i == 0 || (fdres->map[i] && !fdres->map[i + 1]))
			first_last_line_checker(fdres, i);
		while (fdres->map[i][j])
		{
			if (fdres->map[i] && fdres->map[i][j] && fdres->map[i][j] == 32)
				space_checker(fdres, i, j);
			else if (i > 0 && j > 0)
				map_scanning(fdres, i, j);
			j++;
			if (fdres->map[i][j] && !fdres->map[i][j + 1])
				last_carac_checker(fdres, i, j);
		}
		i++;
	}
}
