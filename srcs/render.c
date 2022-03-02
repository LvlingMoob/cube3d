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

int	create_trgb(int t, int r, int g, int b)
{
	if (t > 255)
		t = 255;
	if (t < 0)
		t = 0;
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	return (t << 24 | r << 16 | g << 8 | b);
}

// void	cube_printing(pos, width, height)
// {
// 	;
// }

// void	vector2i(start end)
// {
// 	;
// }

// void	line_printing(start, end, src)
// {
// 	;
// }

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt(((bx - ax) * (bx - ax)) + ((by - ay) * (by - ay))));
}

void	cube_drawing(t_vars *var, int x, int y, int color)
{
	int	i;
	int	j;

	i = x * 16 + 1;
	while (i < (x * 16 + 1) + 14)
	{
		j = y * 16;
		while (j < (y * 16 + 1) + 14)
		{
			my_mlx_pixel_put(var->img,  i, j, color);
			j++;
		}
		i++;
	}
}

void	minimap(t_vars *var)
{
	int	y;
	int	x;

	y = 0;
	while (var->map[y])
	{
		x = 0;
		while (var->map[y][x])
		{
			if (var->map[y][x] == '1')
				cube_drawing(var, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
}

void	plyrpos(t_vars *var)
{
	my_mlx_pixel_put(var->img, 16 * var->plyer->y, 16 * var->plyer->x, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 16 * var->plyer->y + 1, 16 * var->plyer->x, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 16 * var->plyer->y + 1, 16 * var->plyer->x + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 16 * var->plyer->y + 1, 16 * var->plyer->x - 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 16 * var->plyer->y - 1, 16 * var->plyer->x, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 16 * var->plyer->y - 1, 16 * var->plyer->x + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 16 * var->plyer->y - 1, 16 * var->plyer->x - 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 16 * var->plyer->y, 16 * var->plyer->x + 1, 0x00FFFFFF);
	my_mlx_pixel_put(var->img, 16 * var->plyer->y, 16 * var->plyer->x - 1, 0x00FFFFFF);
}

void	draw_top_offset(t_vars *var, float start, int index)
{
	int	i;
	int	j;

	i = 0;
	while (i < start)
	{
		my_mlx_pixel_put(var->img, index, i, 0x000000FF);
		i++;
	}
}

void	draw_wall_part(t_vars *var, float *start, int index, int lineh)
{
	int	i;
	int	end;

	end = S_HEIGHT - (*start);
	while ((*start) < end)
	{
		my_mlx_pixel_put(var->img, index, (*start),  create_trgb(255, lineh / 3, lineh / 3, lineh / 3));
		(*start) += 1;
	}
}

void	draw_bottom_offset(t_vars *var, float start, int index)
{
	int	i;

	while (start < S_HEIGHT)
	{
		my_mlx_pixel_put(var->img, index, start, 0x000000FF);
		start++;
	}
}

void	wall_part(t_vars *var, int start, int end, int index, int lineh)
{
	while (start < end)
	{
		my_mlx_pixel_put(var->img, index, start,  create_trgb(255, lineh / 3, lineh / 3, lineh / 3));
		start++;
	}
}

void	drawRays3D(t_vars *var)
{
	static int whtever = 0;
	double posX = var->plyer->x;
	double posY = var->plyer->y;

	double ra;
	
	ra = var->plyer->orientation;

	if (ra > 360)
		ra -= 360;
	if (ra < 0)
		ra += 360;

	if (!whtever)
	{
		if (ra > 90 && ra < 270)
		{	
			var->dirX = -1;
			var->dirY = 0;
		}
		if ((ra > 270 && ra <= 360)
			|| (ra >= 0 && ra < 90))
		{	
			var->dirX = 1;
			var->dirY = 0;
		}
		if (ra > 0 && ra < 180)
		{	
			var->dirY = 1;
			var->dirX = 0;
		}
		if (ra > 180 && ra < 360)
		{	
			var->dirY = -1;
			var->dirX = 0;
		}
		whtever = 1;
	}
	for(int x = 0; x < S_WIDTH; x++)
	{
		double cameraX = -1 + (x * CAM_SHIFT);
		double rayDirX = var->dirX + var->planeX * cameraX;
		double rayDirY = var->dirY + var->planeY * cameraX;
		int mapX = (int)posX;
		int mapY = (int)posY;

		double sideDistX;
		double sideDistY;
		
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs((1 / rayDirX));
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs((1 / rayDirY));

		double perpWallDist;
		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(var->map[mapX][mapY] == '1')
				hit = 1;
		}

		if(side == 0) 
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		int lineHeight = (int)(S_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + S_HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + S_HEIGHT / 2;
		if(drawEnd >= S_HEIGHT) 
			drawEnd = S_HEIGHT - 1;
		wall_part(var, drawStart, drawEnd, x, lineHeight);
	}
}

int	render_next_frame(t_vars *var)
{
	for (int i = 0; i < S_WIDTH; i++)
	{
		for (int j = 0; j < S_HEIGHT; j++)
			my_mlx_pixel_put(var->img, i, j, 0x00000000);
	}
	drawRays3D(var);
	minimap(var);
	plyrpos(var);

	mlx_put_image_to_window(var->mlx, var->win, var->img->img, 0, 0);
	return (1);
}





























// void	drawRays3D(t_vars *var)
// {
// 	int		r, mx, my, mp, dof, distT, mapX, mapY;
// 	float	rx, ry, hx, hy, vx, vy, ra, xo, yo;


// /*-------------------------------HORIZONTAL-------------------------------*/
// /*------------------------------------------------------------------------*/
// 	mapX = max_width(GET, 0);
// 	mapY = max_height(GET, 0);

// 	ra = var->plyer->orientation - 30;
// 	if (ra < 0)
// 		ra += 360;
// 	if (ra > 360)
// 		ra -= 360;
// 	for (r = 0; r < S_WIDTH ; r++)
// 	{
// 		dof = 0;
// 		float	distH = 10000000000;
// 		hx = var->plyer->x;
// 		hy = var->plyer->y;
// 		float	aTan = -1 / tan(ra * (M_PI / 180));
// 		if (ra > 90 && ra < 270) // looking up
// 		{
// 			ry = (((int)var->plyer->y >> 6) << 6) - 0.0001;
// 			rx = (var->plyer->y - ry) * aTan + var->plyer->x;
// 			yo = -64;
// 			xo = -yo * aTan;
// 		}
// 		if ((ra > 270 && ra < 360) || (ra > 0 && ra < 90)) // looking down
// 		{
// 			ry = (((int)var->plyer->y >> 6) << 6) + 64;
// 			rx = (var->plyer->y - ry) * aTan + var->plyer->x;
// 			yo = 64;
// 			xo = -yo * aTan;
// 		}
// 		if (ra == 90 || ra == 270)
// 		{
// 			rx = var->plyer->x;
// 			ry = var->plyer->y;
// 			dof = 150;
// 		}
// 		while (dof < 150) // dof = depth of field
// 		{
// 			mx = (int)(rx) >> 6;
// 			my = (int)(ry) >> 6;
// 			mp = my * mapX + mx;
// 			if (mp > 0 && mp < mapX * mapY && var->map[mp] == '1') // hit wall
// 			{
// 				hx = rx;
// 				hy = ry;
// 				distH = dist(var->plyer->x, var->plyer->y, hx, hy);
// 				break ;
// 			}
// 			else
// 			{
// 				rx += xo;
// 				ry += yo;
// 				dof += 1;
// 			}
// 		}

// 	/*--------------------------------VERTICAL--------------------------------*/
// 	/*------------------------------------------------------------------------*/
// 		dof = 0;
// 		float	distV = 1000000000;
// 		vx = var->plyer->x;
// 		vy = var->plyer->y;
// 		float naTan = -tan(ra * (M_PI / 180));
// 		if (ra > 180 && ra < 360) // looking left
// 		{
// 			rx = (((int)var->plyer->x >> 6) << 6) - 0.0001;
// 			ry = (var->plyer->x - rx) * naTan + var->plyer->y;
// 			xo = -64;
// 			yo = -xo * naTan;
// 		}
// 		if (ra > 0 || ra < 180) // looking right
// 		{
// 			rx = (((int)var->plyer->x >> 6) << 6) + 64;
// 			ry = (var->plyer->x - rx) * naTan + var->plyer->y;
// 			xo = 64;
// 			yo = -xo * naTan;
// 		}
// 		if (ra == 0 || ra == 180) // up down
// 		{
// 			rx = var->plyer->x;
// 			ry = var->plyer->y;
// 			dof = 150;
// 		}
// 		while (dof < 150) // dof = depth of field
// 		{
// 			mx = (int)(rx) >> 6;
// 			my = (int)(ry) >> 6;
// 			mp = my * mapX + mx;
// 			if (mp > 0 && mp < mapX * mapY && var->map[mp] == '1') // hit wall
// 			{
// 				vx = rx;
// 				vy = ry;
// 				distV = dist(var->plyer->x, var->plyer->y, vx, vy);
// 				break ;
// 			}
// 			else
// 			{
// 				rx += xo;
// 				ry += yo;
// 				dof += 1;
// 			}
// 		}
// 		if (distV < distH)
// 		{
// 			rx = vx;
// 			ry = vy;
// 			distT = distV;
// 		}
// 		if (distH < distV)
// 		{
// 			rx = hx;
// 			ry = hy;
// 			distT = distH;
// 		}
// /*--------------------------3D walls-------------------------------*/
// 		float ca = var->plyer->orientation - ra;
// 		if (ca < 0)
// 			ca += 360;
// 		if (ca > 360)
// 			ca -= 360;
// 		distT = distT * cos(ca * (M_PI / 180));  // fisheye fixer
// 		float lineH = (MAPS * S_HEIGHT) / distT;
// 		float lineO = 160 - lineH / 2;
// 		if (lineH > S_HEIGHT || lineO < 0)
// 			lineO = 0;
// 		printf("%f\n", lineO);
// 		draw_top_offset(var, lineO, r);
// 		draw_wall_part(var, &lineO, r, lineH);
// 		draw_bottom_offset(var, lineO, r);
// /*-----------------------------------------------------------------*/		
// 		ra += SHIFT;
// 		if (ra < 0)
// 			ra += 360;
// 		if (ra > 360)
// 			ra -= 360;
// 	}
// }
