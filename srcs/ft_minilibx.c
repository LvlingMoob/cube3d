/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minilibx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:28:14 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 19:28:15 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_map(t_vars *var)
{
	int	i;
	int	j;

	i = 0;
	while (var->map[i])
	{
		j = 0;
		while (var->map[i][j])
		{
			if (var->map[i][j] == '1')
				my_mlx_pixel_put(var->img, j, i, 0x00FFFFFF);
			j++;
		}
		i++;
	}
}

void	get_distance(t_vars *var, int index, float rx, float ry)
{
	float	x_dist;
	float	y_dist;

	x_dist = rx - var->plyer->x;
	y_dist = ry - var->plyer->y;
	if (x_dist < 0)
		x_dist *= -1;
	if (y_dist < 0)
		y_dist *= -1;
	var->cast_len[index] = sqrt((x_dist * x_dist) + (y_dist * y_dist));
}

void	ray_cast(t_vars *var, int index, int vect)
{
	float	rx;
	float	ry;
	float	xo;
	float	yo;

	xo = cos((var->plyer->orientation + vect) * (M_PI / 180.0));
	yo = sin((var->plyer->orientation + vect) * (M_PI / 180.0));
	rx = var->plyer->x + xo;
	ry = var->plyer->y + yo;
	while (var->map[(int)rx][(int)ry] != '1'
		&& var->map[(int)ceil(rx)][(int)ceil(ry)] != '1')
	{
		rx += xo;
		ry += yo;
	}
	get_distance(var, index, rx, ry);
}

void	draw_vector(t_vars *var, int index, int vect)
{
	float	rx;
	float	ry;
	float	xo;
	float	yo;

	xo = cos((var->plyer->orientation + vect) * (M_PI / 180.0));
	yo = sin((var->plyer->orientation + vect) * (M_PI / 180.0));
	rx = var->plyer->x + xo;
	ry = var->plyer->y + yo;
	while (var->map[(int)rx][(int)ry] != '1'
		&& var->map[(int)ceil(rx)][(int)ceil(ry)] != '1')
	{
		rx += xo;
		ry += yo;
		if (var->map[(int)rx][(int)ry] != '1'
			&& var->map[(int)ceil(rx)][(int)ceil(ry)] != '1')
			my_mlx_pixel_put(var->img, (int)ry, (int)rx, 0x00FF0000);
	}
}

int	x_ok(t_vars *var, int pm)
{
	if (pm == PLUS)
		return (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x + 1][var->plyer->y] != '1');
	else if (pm == MINUS)
		return (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x - 1][var->plyer->y] != '1');
	return (0);
}

int	y_ok(t_vars *var, int pm)
{
	if (pm == PLUS)
		return (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x][var->plyer->y + 1] != '1');
	else if (pm == MINUS)
		return (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x][var->plyer->y - 1] != '1');
	return (0);
}

int	key_press(int key, t_vars *var)
{
	if (key == /*65307*/ 53)
		close_img_win(var);
	else if (/*key == 122*/ key == 13) // UP
	{
		if (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x - 1][var->plyer->y] != '1')
			var->plyer->x--;
	}
	else if (key == /*113*/ 0) // LEFT
	{
		if (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x][var->plyer->y - 1] != '1')
			var->plyer->y--;
	}
	else if (key == /*100*/ 2) // RIGHT
	{
		if (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x][var->plyer->y + 1] != '1')
			var->plyer->y++;
	}
	else if (key == /*115*/ 1) // DOWN
	{
		if (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x + 1][var->plyer->y] != '1')
			var->plyer->x++;
	}
	else if (key == /*65361*/ 123)
	{
		if (var->plyer->orientation + 1 > 360)
			var->plyer->orientation = 0;
		var->plyer->orientation++;
	}
	else if (key == /*65363*/ 124)
	{
		if (var->plyer->orientation - 1 < 0)
			var->plyer->orientation = 360;
		var->plyer->orientation--;
	}
	return (0);
}
