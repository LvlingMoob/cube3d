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

void	floor_and_ceiling_init(t_fd_read *fdres, t_vars *var)
{
	char	**ftmp;
	char	**ctmp;

	ftmp = ft_split(fdres->f, ',');
	ctmp = ft_split(fdres->c, ',');
	var->floor[0] = ft_atoi(ftmp[0]);
	var->floor[1] = ft_atoi(ftmp[1]);
	var->floor[2] = ft_atoi(ftmp[2]);
	var->ceiling[0] = ft_atoi(ctmp[0]);
	var->ceiling[1] = ft_atoi(ctmp[1]);
	var->ceiling[2] = ft_atoi(ctmp[2]);
	ft_free_char_array(ftmp);
	ft_free_char_array(ctmp);
}

void	err_on_xpm_exit(t_fd_read *fdres, t_vars *var)
{
	mlx_destroy_image(var->mlx, var->img->img);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	free(var->plyer);
	free(var->cast_len);
	ft_free_char_array(var->map);
	free_and_quit(fdres, 1);
}

void	xpm__if_bad_size_exit(t_fd_read *fdres, t_vars *var,
				int i, char *texture)
{
	if (i != XPM_WIDTH * XPM_HEIGHT)
	{
		printf("%s bad size\n", texture);
		free_and_quit(fdres, 0);
		close_img_win(var);
	}
}

void	xpm_size_checker(t_fd_read *fdres, t_vars *var)
{
	int	i;

	i = 0;
	while (var->fd_no[i])
		i++;
	xpm__if_bad_size_exit(fdres, var, i, "north texture");
	i = 0;
	while (var->fd_so[i])
		i++;
	xpm__if_bad_size_exit(fdres, var, i, "south texture");
	i = 0;
	while (var->fd_we[i])
		i++;
	xpm__if_bad_size_exit(fdres, var, i, "west texture");
	i = 0;
	while (var->fd_ea[i])
		i++;
	xpm__if_bad_size_exit(fdres, var, i, "east texture");
}

void	fdno_inti(t_fd_read *fdres, t_vars *var, int width, int height)
{
	var->hiero = mlx_xpm_file_to_image(var->mlx, fdres->no,
			&width, &height);
	if (!var->hiero)
		err_on_xpm_exit(fdres, var);
	var->fd_no = (int *)mlx_get_data_addr(var->hiero, &var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
}

void	fdso_inti(t_fd_read *fdres, t_vars *var, int width, int height)
{
	var->world = mlx_xpm_file_to_image(var->mlx, fdres->so,
			&width, &height);
	if (!var->world)
	{
		mlx_destroy_image(var->mlx, var->hermit);
		mlx_destroy_image(var->mlx, var->chariot);
		mlx_destroy_image(var->mlx, var->hiero);
		err_on_xpm_exit(fdres, var);
	}
	var->fd_so = (int *)mlx_get_data_addr(var->world,
			&var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
}

void	fdwe_inti(t_fd_read *fdres, t_vars *var, int width, int height)
{
	var->chariot = mlx_xpm_file_to_image(var->mlx, fdres->we,
			&width, &height);
	if (!var->chariot)
	{
		mlx_destroy_image(var->mlx, var->hiero);
		err_on_xpm_exit(fdres, var);
	}
	var->fd_we = (int *)mlx_get_data_addr(var->chariot,
			&var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
}

void	fdea_inti(t_fd_read *fdres, t_vars *var, int width, int height)
{
	var->hermit = mlx_xpm_file_to_image(var->mlx, fdres->ea,
			&width, &height);
	if (!var->hermit)
	{
		mlx_destroy_image(var->mlx, var->chariot);
		mlx_destroy_image(var->mlx, var->hiero);
		err_on_xpm_exit(fdres, var);
	}
	var->fd_ea = (int *)mlx_get_data_addr(var->hermit,
			&var->img->bits_per_pixel,
			&var->img->line_length, &var->img->endian);
}

void	get_textures(t_fd_read *fdres, t_vars *var)
{
	int	width;
	int	height;

	width = XPM_WIDTH;
	height = XPM_HEIGHT;
	fdno_inti(fdres, var, width, height);
	fdwe_inti(fdres, var, width, height);
	fdea_inti(fdres, var, width, height);
	fdso_inti(fdres, var, width, height);
	xpm_size_checker(fdres, var);
	floor_and_ceiling_init(fdres, var);
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
