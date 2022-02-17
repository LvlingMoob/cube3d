#include "cube.h"

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
			first_last_line_checker(fdres, i);
		while (fdres->map[i][j])
		{
			if (fdres->map[i] && fdres->map[i][j] && fdres->map[i][j] == 32)
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
