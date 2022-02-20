#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_map(t_vars *var)
{
	for (int i = 0; var->map[i]; i++)
	{
		for (int j = 0; var->map[i][j]; j++)
		{
			if (var->map[i][j] == '1')
				my_mlx_pixel_put(var->img, j, i, 0x00FFFFFF);
		}
	}
}

void	draw_vector(t_vars *var, int index, int vect)
{
	int		dof;
	float	rx;
	float	ry;
	float	xo;
	float	yo;

	dof = 0;
	xo = cos((var->plyer->orientation + vect) * (M_PI / 180.0));
	yo = sin((var->plyer->orientation + vect) * (M_PI / 180.0));
	rx = var->plyer->x + xo;
	ry = var->plyer->y + yo;
	while (var->map[(int)rx][(int)ry] != '1')
	{
		rx += xo;
		ry += yo;
		dof += 1;
		if (var->map[(int)rx][(int)ry] != '1')
			my_mlx_pixel_put(var->img, (int)ry, (int)rx, 0x00FF0000);
	}
	float x_dist = rx - var->plyer->x;
	float y_dist = ry - var->plyer->y;
	if (x_dist < 0)
		x_dist *= -1;
	if (y_dist < 0)
		y_dist *= -1;
	var->cast_len[index] = sqrt((x_dist * x_dist) + (y_dist * y_dist));
}

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

void	draw_wall(t_vars *var, int index, int vect)
{
	float	lineH;
	float	lineO;
	float	distT;

	distT = var->cast_len[index] * cos((var->plyer->orientation - (var->plyer->orientation + vect)) * (M_PI / 180.0));
	lineH = (16 * 100) / distT;
	lineO = 400 - lineH;
	if (lineH > 800)
		lineH = 800;
	int start = lineO / 2;
	int k = 0;
	while (k < start && lineH < 800)
	{
		for (int i = 0; i < 10; i++)
			my_mlx_pixel_put(var->img, 800 - (index * 10) + i, k, 0x000000FF);
		k++;
	}
	int j = start;
	int l = 600 - start;
	while (j < l)
	{
		for (int i = 0; i < 10; i++)
			my_mlx_pixel_put(var->img, 800 - (index * 10) + i, j, create_trgb(255, 255 * 10 * (1 / distT), 255 * 10 * (1 / distT), 255 * 10 * (1 / distT)));
		j++;
	}
	while (j < 600 && lineH < 800)
	{
		for (int i = 0; i < 10; i++)
			my_mlx_pixel_put(var->img, 800 - (index * 10) + i, j, 0x000000FF);
		j++;	
	}
}

int	render_next_frame(t_vars *var)
{
	int index;
	float	vect;

	for (int i = 0; i < S_WIDTH; i++)
	{
		for (int j = 0; j < S_HEIGHT; j++)
			my_mlx_pixel_put(var->img, i, j, 0x00000000);
	}
	index = 0;
	vect = -30;
	while (index < 80)
	{
		draw_vector(var, index, vect);
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

int	key_press(int key, t_vars *var)
{
	if (key == 65307)
		close_img_win(var);
	else if (key == 122) // UP
	{
		if (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x - 1][var->plyer->y] != '1')
			var->plyer->x--;
	}
	else if (key == 113)// LEFT
	{
		if (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x][var->plyer->y - 1] != '1')
			var->plyer->y--;
	}
	else if (key == 100)// RIGHT
	{
		if (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x][var->plyer->y + 1] != '1')
			var->plyer->y++;
	}
	else if (key == 115)// DOWN
	{
		if (var->map[var->plyer->x][var->plyer->y]
			&& var->map[var->plyer->x + 1][var->plyer->y] != '1')
			var->plyer->x++;
	}
	else if (key == 65361)
	{
		if (var->plyer->orientation + 1 > 360)
			var->plyer->orientation = 0;
		var->plyer->orientation++;
	}
	else if (key == 65363)
	{
		if (var->plyer->orientation - 1 < 0)
			var->plyer->orientation = 360;
		var->plyer->orientation--;
	}
	return (0);
}
