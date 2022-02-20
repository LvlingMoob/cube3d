/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:59:22 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 20:59:24 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_top_offset(t_vars *var, int start, int index)
{
	int	i;
	int	j;

	i = 0;
	while (i < start)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(var->img, 800 - (index * 10) + j, i, 0x000000FF);
			j++;
		}
		i++;
	}
}

void	draw_wall_part(t_vars *var, int *start, int index)
{
	int	i;
	int	end;

	end = 600 - (*start);
	while ((*start) < end)
	{
		i = 0;
		while (i < 10)
		{
			my_mlx_pixel_put(var->img, 800 - (index * 10) + i,
				(*start), 0x00FFFF00);
			i++;
		}
		(*start) += 1;
	}
}

void	draw_bottom_offset(t_vars *var, int start, int index)
{
	int	i;

	while (start < 600)
	{
		i = 0;
		while (i < 10)
		{
			my_mlx_pixel_put(var->img, 800 - (index * 10) + i, start,
				0x000000FF);
			i++;
		}
		start++;
	}
}

void	draw_wall(t_vars *var, int index, int vect)
{
	float	lineh;
	float	lineo;
	float	dist;
	int		start;

	dist = var->cast_len[index] * cos((var->plyer->orientation
				- (var->plyer->orientation + vect)) * (M_PI / 180.0));
	lineh = (16 * 500) / dist;
	lineo = 800 - (lineh * 2);
	if (lineh > 400.0)
		lineo = 0;
	start = lineo / 2;
	draw_top_offset(var, start, index);
	draw_wall_part(var, &start, index);
	draw_bottom_offset(var, start, index);
}

int	render_next_frame(t_vars *var)
{
	int		index;
	float	vect;

	for (int i = 0; i < S_WIDTH; i++)
	{
		for (int j = 0; j < S_HEIGHT; j++)
			my_mlx_pixel_put(var->img, i, j, 0x00000000);
	}
	index = 0;
	vect = -30;
	draw_map(var);
	while (index < 80)
	{
		ray_cast(var, index, vect);
		index++;
		vect += 0.5;
	}
	index = 0;
	vect = -30;
	while (index < 80)
	{
		draw_wall(var, index, vect);
		index++;
		vect += 0.5;
	}
	index = 0;
	vect = -30;
	draw_map(var);
	while (index < 80)
	{
		draw_vector(var, index, vect);
		index++;
		vect += 0.5;
	}
	my_mlx_pixel_put(var->img, var->plyer->y, var->plyer->x, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->y + 1, var->plyer->x, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->y + 1, var->plyer->x + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->y + 1, var->plyer->x - 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->y - 1, var->plyer->x, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->y - 1, var->plyer->x + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->y - 1, var->plyer->x - 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->y, var->plyer->x + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, var->plyer->y, var->plyer->x - 1, 0x00FFFFFF);

	mlx_put_image_to_window(var->mlx, var->win, var->img->img, 0, 0);
	return (1);
}
