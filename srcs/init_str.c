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

void	cp_char_array_multiply(char ***dest, char **src, int mult)
{
	int		i;
	int		j;
	int		l;
	int		k;
	int		row;
	char	*tmp;

	i = 0;
	while (src[i])
		i++;
	(*dest) = ft_calloc((i * mult) + 1, sizeof(char *));
	i = 0;
	k = 0;
	while (src[i])
	{
		j = 0;
		tmp = ft_calloc(1, sizeof(char));
		l = 0;
		while (src[i][j])
		{
			tmp = str_char_cat(tmp, src[i][j]);
			l++;
			if (!(l % mult))
				j++;
		}
		row = 0;
		while (row < mult)
		{
			(*dest)[k] = ft_strdup(tmp);
			k++;
			row++;
		}
		free(tmp);
		i++;
	}
}

void	var_plyer_init(t_vars *var, t_fd_read *fdres, int mult)
{
	int	i;
	int	j;
	int	orientation;

	i = 0;
	cp_char_array_multiply(&var->map, fdres->map, mult);
	var->plyer = ft_calloc(1, sizeof(t_plyer));
	while (fdres->map[i])
	{
		j = 0;
		while (fdres->map[i][j])
		{
			if (fdres->map[i][j] == 'N' || fdres->map[i][j] == 'S' || fdres->map[i][j] == 'W' || fdres->map[i][j] == 'E')
			{
				var->plyer->x = (i * mult) - (mult / 2);
				var->plyer->y = (j * mult) - (mult / 2);
				if (fdres->map[i][j] == 'N')
					orientation = NO;
				else if (fdres->map[i][j] == 'S')
					orientation = SO;
				else if (fdres->map[i][j] == 'W')
					orientation = WE;
				else if (fdres->map[i][j] == 'E')
					orientation = EA;
			}	
			j++;
		}
		i++;
	}
	var->cast_len = ft_calloc(60, sizeof(float));
	if (orientation ==  NO)
		var->plyer->orientation = 180;
	else if (orientation ==  SO)
		var->plyer->orientation = 0;
	else if (orientation ==  WE)
		var->plyer->orientation = 270;
	else if (orientation ==  EA)
		var->plyer->orientation = 90;
}

