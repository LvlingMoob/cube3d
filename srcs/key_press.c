/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:11:29 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 20:11:30 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	key_var_init(t_key *key_var, t_vars *var)
{
	key_var->olddirx = var->dirX;
	key_var->oldplanex = var->planeX;
	key_var->rotspeed = 2 * (M_PI / 180);
	key_var->movespeed = 0.1;
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
