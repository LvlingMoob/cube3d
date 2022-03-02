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
	var->planeX = 0.0;
	var->planeY = 0.66;
}
