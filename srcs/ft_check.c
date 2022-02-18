#include "cube.h"

void	first_carac_checker(t_fd_read *fdres, int i)
{
	int	j;

	j = 0;
	while (fdres->map[i][j] && (fdres->map[i][j] > 0 && fdres->map[i][j] <= 32))
	{
		if (!authorized_char(fdres->map[i][j]))
			free_and_quit(fdres, 1);
		j++;
	}
	if (fdres->map[i][j] != '1')
		free_and_quit(fdres, 1);
}

void	last_carac_checker(t_fd_read *fdres, int i, int j)
{
	int	k;

	k = 0;
	while (j - k > 0 && (fdres->map[i][j - k] > 0 && fdres->map[i][j - k] <= 32)) // too long
	{
		if (!authorized_char(fdres->map[i][j - k]))
			free_and_quit(fdres, 1);
		k++;
	}
	if (fdres->map[i][j - k] != '1')
		free_and_quit(fdres, 1);
}

void	map_scanning(t_fd_read *fdres, int i, int j)
{
	if ((fdres->map[i][j] != '1' && fdres->map[i][j] != 32
		&& (fdres->map[i + 1][j] == 32
			|| (fdres->map[i][j] && fdres->map[i][j + 1] && fdres->map[i + 1][j + 1] == 32) // too long
			|| fdres->map[i + 1][j - 1] == 32
			|| fdres->map[i - 1][j] == 32
			|| (fdres->map[i][j] && fdres->map[i][j + 1] && fdres->map[i - 1][j + 1] == 32) // too long
			|| fdres->map[i - 1][j - 1] == 32
			|| (fdres->map[i][j] && fdres->map[i][j + 1] && fdres->map[i][j + 1] == 32) // too long
			|| fdres->map[i][j - 1] == 32))
		|| !authorized_char(fdres->map[i][j]))
		free_and_quit(fdres, 1);
}

void	space_checker(t_fd_read *fdres, int i, int j)
{
	int	k;
	int	l;

	k = 0;
	l = 0;
	while (fdres->map[i][j + l] && (fdres->map[i][j + l] > 0 && fdres->map[i][j + l] <= 32)) // too long
	{
		if (!authorized_char(fdres->map[i][j + l]))
			free_and_quit(fdres, 1);
		l++;
	}
	while (j - k > 0 && fdres->map[i][j - k] && (fdres->map[i][j - k] > 0 && fdres->map[i][j - k] <= 32)) // too long
	{
		if (!authorized_char(fdres->map[i][j - k]))
			free_and_quit(fdres, 1);
		k++;
	}
	if ((fdres->map[i][j + l] != '1' && fdres->map[i][j + l]) || (fdres->map[i][j - k] != '1' && j - k != 0)) // too long
		free_and_quit(fdres, 1);
}

void	first_last_line_checker(t_fd_read *fdres, int i)
{
	int	j;

	j = 0;
	while (fdres->map[i][j])
	{
		if (fdres->map[i][j] != 32 && fdres->map[i][j] != '1')
			free_and_quit(fdres, 1);
		j++;
	}
}
