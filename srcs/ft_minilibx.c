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
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;

	start_x = var->plyer->x + 0.5;
	start_x = var->plyer->y + 0.5;
	end_x = var->plyer->x;
	end_y = var->plyer->y;
	while (var->map[(int)ceil(end_x)][(int)ceil(end_y)] != '1'
		&& (sqrt((end_x * end_x) + (end_y * end_y))) > 50)
	{
		end_x += cos((var->plyer->orientation + vect) * (M_PI / 180.0));
		end_y += sin((var->plyer->orientation + vect) * (M_PI / 180.0));
		if (var->map[(int)ceil(end_x)][(int)ceil(end_y)] != '1')
			my_mlx_pixel_put(var->img, (int)ceil(end_y), (int)ceil(end_x), 0x00FF0000);
	}
	var->cast_len[index] = sqrt((end_x * end_x) + (end_y * end_y));
}

int	render_next_frame(t_vars *var)
{
	int index;
	int	vect;

	index = 0;
	vect = -30;
	for (int i = 0; i < S_WIDTH; i++)
	{
		for (int j = 0; j < S_HEIGHT; j++)
			my_mlx_pixel_put(var->img, i, j, 0x00000000);
	}
	draw_map(var);
	while (index < 60)
	{
		draw_vector(var, index, vect);
		index++;
		vect++;
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
