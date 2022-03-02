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

int	key_press(int key, t_vars *var)
{
	double oldDirX = var->dirX;
	double oldPlaneX = var->planeX;
	double rotSpeed = 2 * (M_PI / 180);
	double moveSpeed = 0.1;
	double tmpdirX;
	double tmpdirY;

	if (key == 65307)
		close_img_win(var);
	else if (key == 122) // UP
	{
		if(var->map[(int)(var->plyer->x + var->dirX * moveSpeed)][(int)(var->plyer->y)] == '0') var->plyer->x += (float)(var->dirX * moveSpeed);
		if(var->map[(int)(var->plyer->x)][(int)(var->plyer->y + var->dirY * moveSpeed)] == '0') var->plyer->y += (float)(var->dirY * moveSpeed);
	}
	else if (key == 113) // LEFT
	{
		tmpdirX = var->dirX * cos(90 * (M_PI / 180)) - var->dirY * sin(90 * (M_PI / 180));
		tmpdirY = oldDirX * sin(90 * (M_PI / 180)) + var->dirY * cos(90 * (M_PI / 180));
		if(var->map[(int)(var->plyer->x + tmpdirX * moveSpeed)][(int)(var->plyer->y)] == '0') var->plyer->x += (float)(tmpdirX * moveSpeed);
		if(var->map[(int)(var->plyer->x)][(int)(var->plyer->y + tmpdirY * moveSpeed)] == '0') var->plyer->y += (float)(tmpdirY * moveSpeed);
	}
	else if (key == 100) // RIGHT
	{
		tmpdirX = var->dirX * cos(-90 * (M_PI / 180)) - var->dirY * sin(-90 * (M_PI / 180));
		tmpdirY = oldDirX * sin(-90 * (M_PI / 180)) + var->dirY * cos(-90 * (M_PI / 180));
		if(var->map[(int)(var->plyer->x + tmpdirX * moveSpeed)][(int)(var->plyer->y)] == '0') var->plyer->x += (float)(tmpdirX * moveSpeed);
		if(var->map[(int)(var->plyer->x)][(int)(var->plyer->y + tmpdirY * moveSpeed)] == '0') var->plyer->y += (float)(tmpdirY * moveSpeed);
	}
	else if (key == 115) // DOWN
	{
		if(var->map[(int)(var->plyer->x - var->dirX * moveSpeed)][(int)(var->plyer->y)] == '0') var->plyer->x -= var->dirX * moveSpeed;
		if(var->map[(int)(var->plyer->x)][(int)(var->plyer->y - var->dirY * moveSpeed)] == '0') var->plyer->y -= var->dirY * moveSpeed;
	}
	else if (key == 65361)
	{
		var->dirX = var->dirX * cos(rotSpeed) - var->dirY * sin(rotSpeed);
		var->dirY = oldDirX * sin(rotSpeed) + var->dirY * cos(rotSpeed);
		var->planeX = var->planeX * cos(rotSpeed) - var->planeY * sin(rotSpeed);
		var->planeY = oldPlaneX * sin(rotSpeed) + var->planeY * cos(rotSpeed);
	}
	else if (key == 65363)
	{
		var->dirX = var->dirX * cos(-rotSpeed) - var->dirY * sin(-rotSpeed);
		var->dirY = oldDirX * sin(-rotSpeed) + var->dirY * cos(-rotSpeed);
		var->planeX = var->planeX * cos(-rotSpeed) - var->planeY * sin(-rotSpeed);
		var->planeY = oldPlaneX * sin(-rotSpeed) + var->planeY * cos(-rotSpeed);
	}
	return (0);
}
