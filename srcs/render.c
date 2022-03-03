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

void	cam_orientation_setup(t_ray *cast, t_vars *var, int x)
{
	cast->camerax = -1 + (x * CAM_SHIFT);
	cast->raydirx = var->dirX + var->planeX * cast->camerax;
	cast->raydiry = var->dirY + var->planeY * cast->camerax;
	cast->mapx = (int)cast->posx;
	cast->mapy = (int)cast->posy;
	if (cast->raydirx == 0)
		cast->deltadistx = 1e30;
	else
		cast->deltadistx = fabs((1 / cast->raydirx));
	if (cast->raydiry == 0)
		cast->deltadisty = 1e30;
	else
		cast->deltadisty = fabs((1 / cast->raydiry));
}

void	vector_step_setup(t_ray *cast, t_vars *var)
{
	if (cast->raydirx < 0)
	{
		cast->stepx = -1;
		cast->sidedistx = (cast->posx - cast->mapx) * cast->deltadistx;
	}
	else
	{
		cast->stepx = 1;
		cast->sidedistx = (cast->mapx + 1.0 - cast->posx) * cast->deltadistx;
	}
	if (cast->raydiry < 0)
	{
		cast->stepy = -1;
		cast->sidedisty = (cast->posy - cast->mapy) * cast->deltadisty;
	}
	else
	{
		cast->stepy = 1;
		cast->sidedisty = (cast->mapy + 1.0 - cast->posy) * cast->deltadisty;
	}
}

void	perform_dda(t_ray *cast, t_vars *var)
{
	while (cast->hit == 0)
	{
		if (cast->sidedistx < cast->sidedisty)
		{
			cast->sidedistx += cast->deltadistx;
			cast->mapx += cast->stepx;
			cast->side = 0;
		}
		else
		{
			cast->sidedisty += cast->deltadisty;
			cast->mapy += cast->stepy;
			cast->side = 1;
		}
		if (var->map[cast->mapx][cast->mapy] == '1')
			cast->hit = 1;
	}
}

void	set_drawing_area(t_ray *cast, t_vars *var)
{
	if (cast->side == 0)
		cast->perpwalldist = (cast->sidedistx - cast->deltadistx);
	else
		cast->perpwalldist = (cast->sidedisty - cast->deltadisty);
	cast->lineheight = (int)(S_HEIGHT / cast->perpwalldist);
	cast->drawstart = -cast->lineheight / 2 + S_HEIGHT / 2 + cast->pitch;
	if (cast->drawstart < 0)
		cast->drawstart = 0;
	cast->drawend = cast->lineheight / 2 + S_HEIGHT / 2 + cast->pitch;
	if (cast->drawend >= S_HEIGHT)
		cast->drawend = S_HEIGHT - 1;
}

void	set_texture(t_ray *cast, t_vars *var)
{
	if (cast->side == 0)
		cast->wallx = cast->posy + cast->perpwalldist * cast->raydiry;
	else
		cast->wallx = cast->posx + cast->perpwalldist * cast->raydirx;
	cast->wallx -= floor((cast->wallx));
	cast->texx = (int)(cast->wallx * (double)(texWidth));
	if (cast->side == 0 && cast->raydirx > 0)
		cast->texx = texWidth - cast->texx - 1;
	if (cast->side == 1 && cast->raydiry < 0)
		cast->texx = texWidth - cast->texx - 1;
	cast->step = 1.0 * texHeight / cast->lineheight;
	cast->texpos = (cast->drawstart - cast->pitch
			- S_HEIGHT / 2 + cast->lineheight / 2) * cast->step;
}

void	draw(t_ray *cast, t_vars *var, int x)
{
	while (cast->drawstart < cast->drawend)
	{
		cast->texy = (int)cast->texpos & (texHeight - 1);
		cast->texpos += cast->step;
		if (cast->side)
		{
			if (cast->stepy == 1)
				cast->color = var->fd_ea[texHeight * cast->texy + cast->texx];
			else
				cast->color = var->fd_we[texHeight * cast->texy + cast->texx];
		}
		else if (!cast->side)
		{
			if (cast->stepx == 1)
				cast->color = var->fd_so[texHeight * cast->texy + cast->texx];
			else
				cast->color = var->fd_no[texHeight * cast->texy + cast->texx];
		}
		else
			cast->color = 0x0FFFFFF;
		my_mlx_pixel_put(var->img, x, cast->drawstart,
			create_trgb(255,
				get_r(cast->color), get_g(cast->color), get_b(cast->color)));
		cast->drawstart++;
	}
}

void	rayscasting(t_vars *var)
{
	int		x;
	t_ray	cast;

	x = 0;
	cast.pitch = 100;
	cast.posx = var->plyer->x;
	cast.posy = var->plyer->y;
	while (x < S_WIDTH)
	{
		cam_orientation_setup(&cast, var, x);
		cast.hit = 0;
		vector_step_setup(&cast, var);
		perform_dda(&cast, var);
		set_drawing_area(&cast, var);
		set_texture(&cast, var);
		draw(&cast, var, x);
		x++;
	}
}

int	render_next_frame(t_vars *var)
{
	int	i;
	int	j;

	i = 0;
	while (i < S_WIDTH)
	{
		j = 0;
		while (j < S_HEIGHT)
		{
			my_mlx_pixel_put(var->img, i, j, 0x00000000);
			j++;
		}
		i++;
	}
	rayscasting(var);
	minimap(var);
	plyrpos(var);
	mlx_put_image_to_window(var->mlx, var->win, var->img->img, 0, 0);
	return (1);
}
