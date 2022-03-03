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

void	key_var_init(t_key *key_var, t_vars *var)
{
	key_var->olddirx = var->dirX;
	key_var->oldplanex = var->planeX;
	key_var->rotspeed = 2 * (M_PI / 180);
	key_var->movespeed = 0.1;
}

void	up(t_key key_var, t_vars *var)
{
	if (var->map[(int)(var->plyer->x + var->dirX * key_var.movespeed)]
			[(int)(var->plyer->y)] == '0')
		var->plyer->x += (float)(var->dirX * key_var.movespeed);
	if (var->map[(int)(var->plyer->x)]
			[(int)(var->plyer->y + var->dirY * key_var.movespeed)] == '0')
		var->plyer->y += (float)(var->dirY * key_var.movespeed);
}

void	down(t_key key_var, t_vars *var)
{
	if (var->map[(int)(var->plyer->x - var->dirX * key_var.movespeed)]
			[(int)(var->plyer->y)] == '0')
		var->plyer->x -= var->dirX * key_var.movespeed;
	if (var->map[(int)(var->plyer->x)]
			[(int)(var->plyer->y - var->dirY * key_var.movespeed)] == '0')
		var->plyer->y -= var->dirY * key_var.movespeed;
}

void	strafe_left(t_key key_var, t_vars *var)
{
	key_var.tmpdirx = var->dirX * cos(90 * (M_PI / 180))
		- var->dirY * sin(90 * (M_PI / 180));
	key_var.tmpdiry = key_var.olddirx * sin(90 * (M_PI / 180))
		+ var->dirY * cos(90 * (M_PI / 180));
	if (var->map[(int)(var->plyer->x + key_var.tmpdirx * key_var.movespeed)]
			[(int)(var->plyer->y)] == '0')
		var->plyer->x += (float)(key_var.tmpdirx * key_var.movespeed);
	if (var->map[(int)(var->plyer->x)]
			[(int)(var->plyer->y + key_var.tmpdiry * key_var.movespeed)] == '0')
		var->plyer->y += (float)(key_var.tmpdiry * key_var.movespeed);
}

void	strafe_right(t_key key_var, t_vars *var)
{
	key_var.tmpdirx = var->dirX * cos(-90 * (M_PI / 180))
		- var->dirY * sin(-90 * (M_PI / 180));
	key_var.tmpdiry = key_var.olddirx * sin(-90 * (M_PI / 180))
		+ var->dirY * cos(-90 * (M_PI / 180));
	if (var->map[(int)(var->plyer->x + key_var.tmpdirx * key_var.movespeed)]
			[(int)(var->plyer->y)] == '0')
		var->plyer->x += (float)(key_var.tmpdirx * key_var.movespeed);
	if (var->map[(int)(var->plyer->x)]
			[(int)(var->plyer->y + key_var.tmpdiry * key_var.movespeed)] == '0')
		var->plyer->y += (float)(key_var.tmpdiry * key_var.movespeed);
}

void	turn_left(t_key key_var, t_vars *var)
{
	var->dirX = var->dirX * cos(key_var.rotspeed)
		- var->dirY * sin(key_var.rotspeed);
	var->dirY = key_var.olddirx * sin(key_var.rotspeed)
		+ var->dirY * cos(key_var.rotspeed);
	var->planeX = var->planeX * cos(key_var.rotspeed)
		- var->planeY * sin(key_var.rotspeed);
	var->planeY = key_var.oldplanex * sin(key_var.rotspeed)
		+ var->planeY * cos(key_var.rotspeed);
}

void	turn_right(t_key key_var, t_vars *var)
{
	var->dirX = var->dirX * cos(-key_var.rotspeed)
		- var->dirY * sin(-key_var.rotspeed);
	var->dirY = key_var.olddirx * sin(-key_var.rotspeed)
		+ var->dirY * cos(-key_var.rotspeed);
	var->planeX = var->planeX * cos(-key_var.rotspeed)
		- var->planeY * sin(-key_var.rotspeed);
	var->planeY = key_var.oldplanex * sin(-key_var.rotspeed)
		+ var->planeY * cos(-key_var.rotspeed);
}

int	key_press(int key, t_vars *var)
{
	t_key	key_var;

	key_var_init(&key_var, var);
	if (key == 65307)
		close_img_win(var);
	else if (key == UP)
		up(key_var, var);
	else if (key == LEFT)
		strafe_left(key_var, var);
	else if (key == RIGHT)
		strafe_right(key_var, var);
	else if (key == DOWN)
		down(key_var, var);
	else if (key == L_ROT)
		turn_left(key_var, var);
	else if (key == R_ROT)
		turn_right(key_var, var);
	return (0);
}
