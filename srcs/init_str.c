/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:28:22 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 19:28:23 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

void	get_start_orientation(t_vars *var, char c)
{
	if (c == 'N')
		var->plyer->orientation = 180;
	else if (c == 'S')
		var->plyer->orientation = 0;
	else if (c == 'W')
		var->plyer->orientation = 270;
	else if (c == 'E')
		var->plyer->orientation = 90;
	var->plyer->pdx = cos(var->plyer->orientation * (M_PI / 180));
	var->plyer->pdy = sin(var->plyer->orientation * (M_PI / 180));

	double ra;
	
	ra = var->plyer->orientation;

	if (ra > 90 && ra < 270)
	{	
		var->dirX = -1;
		var->dirY = 0;
		var->planeX = 0.0;
		var->planeY = 0.66;
	}
	if ((ra > 270 && ra <= 360)
		|| (ra >= 0 && ra < 90))
	{	
		var->dirX = 1;
		var->dirY = 0;
		var->planeX = 0;
		var->planeY = -0.66;
	}
	if (ra > 0 && ra < 180)
	{	
		var->dirY = 1;
		var->dirX = 0;
		var->planeX = 0.66;
		var->planeY = 0;
	}
	if (ra > 180 && ra < 360)
	{	
		var->dirY = -1;
		var->dirX = 0;
		var->planeX = -0.66;
		var->planeY = 0;
		
	}
}


void	var_plyer_init(t_vars *var, t_fd_read *fdres, int mult)
{
	int	i;
	int	j;

	i = 0;
	var->plyer = ft_calloc(1, sizeof(t_plyer));
	var->cast_len = ft_calloc(S_WIDTH, sizeof(int));
	while (fdres->map[i])
	{
		j = 0;
		while (fdres->map[i][j])
		{
			if (fdres->map[i][j] == 'N' || fdres->map[i][j] == 'S'
				|| fdres->map[i][j] == 'W' || fdres->map[i][j] == 'E')
			{
				var->plyer->x = i + 0.5;
				var->plyer->y = j + 0.5;
				get_start_orientation(var, fdres->map[i][j]);
				fdres->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	cp_char_array(&var->map, fdres->map);
	
}



// int width = 64;
// int height = 64;
// int	*ret;
// void *test = mlx_xpm_file_to_image(var.mlx, argv[1], &width, &height);

// ret = ft_calloc(1, sizeof(int));
// ret = (int *)mlx_get_data_addr(test, &img.bits_per_pixel, &img.line_length, &img.endian);
// while (*ret)
// 	printf("%d\n", *(ret++));