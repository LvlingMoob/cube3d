#include "cube.h"

void	first_carac_checker(t_fd_read *fdres, int i)
{
	int	j;

	j = 0;
	while (fdres->map[i][j] && (fdres->map[i][j] > 0 && fdres->map[i][j] <= 32))
		j++;
	if (fdres->map[i][j] != '1')
		free_and_quit(fdres);
}


int	digit_value_checker(t_fd_read *fdres, char *values, int l)
{
	int		i;
	int		j;
	char	**tmp_checker;

	i = 0;
	tmp_checker = ft_split(values, ',');
	while (tmp_checker[i])
	{
		j = 0;
		while (tmp_checker[i][j])
		{
			if (tmp_checker[i][j] > 0 && tmp_checker[i][j] <= 32)
				tmp_checker[i][j] = 32;
			if (!ft_isdigit(tmp_checker[i][j]) && tmp_checker[i][j] != 32)
			{
				ft_free_char_array(tmp_checker);
				return (0);
			}
			j++;
		}
		i++;
	}
	if (i > 3)
	{
		printf("l %d : %s : error 3 numbers expected\n", l, values);
		ft_free_char_array(tmp_checker);
		free_and_quit(fdres);
	}
	ft_free_char_array(tmp_checker);
	return (1);
}

void	map_scanning(t_fd_read *fdres, int i, int j)
{
	if (fdres->map[i][j] != '1' && fdres->map[i][j] != 32
		&& (fdres->map[i + 1][j] == 32
			|| (fdres->map[i][j] && fdres->map[i][j + 1] && fdres->map[i + 1][j + 1] == 32)
			|| fdres->map[i + 1][j - 1] == 32
			|| fdres->map[i - 1][j] == 32
			|| (fdres->map[i][j] && fdres->map[i][j + 1] && fdres->map[i - 1][j + 1] == 32)
			|| fdres->map[i - 1][j - 1] == 32
			|| (fdres->map[i][j] && fdres->map[i][j + 1] && fdres->map[i][j + 1] == 32)
			|| fdres->map[i][j - 1] == 32))
		free_and_quit(fdres);
}

void	space_checker(t_fd_read *fdres, int i, int j)
{
	int	k;
	int	l;

	k = 0;
	l = 0;
	while (fdres->map[i][j + l] && (fdres->map[i][j + l] > 0 && fdres->map[i][j + l] <= 32))
		l++;
	while (j - k >= 0 && fdres->map[i][j - k] && (fdres->map[i][j - k] > 0 && fdres->map[i][j - k] <= 32))
		k++;
	if ((fdres->map[i][j + l] != '1' && fdres->map[i][j + l]) || (fdres->map[i][j - k] != '1' && j - k != 0))
		free_and_quit(fdres);
}

void	last_carac_checker(t_fd_read *fdres, int i, int j)
{
	int	k;

	k = 0;
	while (j - k >= 0 && (fdres->map[i][j - k] > 0 && fdres->map[i][j - k] <= 32))
		k++;
	if (fdres->map[i][j - k] != '1')
		free_and_quit(fdres);
}

void	ends_line_checker(t_fd_read *fdres, int i)
{
	int	j;

	j = 0;
	while (fdres->map[i][j])
	{
		if (fdres->map[i][j] != 32 && fdres->map[i][j] != '1')
			free_and_quit(fdres);
		j++;
	}
}
void	map_checker(t_fd_read *fdres)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (fdres->map[i])
	{
		j = 0;
		printf("-->%s\n", fdres->map[i]);
		first_carac_checker(fdres, i);
		if (i == 0 || (fdres->map[i] && !fdres->map[i + 1]))
			ends_line_checker(fdres, i);
		while (fdres->map[i][j])
		{
			if (fdres->map[i][j] == 32)
				space_checker(fdres, i, j);
			else if (i > 0 && j > 0)
				map_scanning(fdres, i, j);
			j++;
			if (fdres->map[i][j] && !fdres->map[i][j + 1])
				last_carac_checker(fdres, i, j);
		}
		i++;
	}
}
