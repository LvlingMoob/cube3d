#include "cube.h"

// int	authorized_char(char c)
// {
// 	static int	plyer_set = 0;

// 	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
// 	{
// 		if (!plyer_set)
// 			plyer_set = 1;
// 		else
// 			return (0);
// 	}
// 	return (c == '0' || c == '1'  || c == '\n' || c == 32
// 		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
// }

int	init_i(char *line, int start)
{
	int	i;

	i = 0;
	if (line[i] > 0 && line[i] <= 32)
	{
		while (line[i] && line[i] > 0 && line[i] <= 32)
			i++;
		i += start;
	}
	else
		i = start;
	return (i);
}

int	start_line_checker(char *line, int *j, int l)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] > 0 && line[i] <= 32))
		i++;
	if (!line[i])
	{
		printf("l %d : %s : error, empty lines\n", l, line);
		return (0);
	}
	*j = i;
	while (line[i] && !(line[i] > 0 && line[i] <= 32))
		i++;
	return (i);
}

int	end_line_checker(char *line, int l)
{
	int	i;

	i = 0;
	if (line[i])
	{
		while (line[i])
		{
			if (!(line[i] > 0 && line[i] <= 32))
			{
				printf("l %d : '%c' : error, unexpected value\n", l, line[i]);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

void	err_print(t_fd_read *fdres, char *expected_value, int l)
{
	char	*tmp;

	tmp = ft_itoa(l);
	ft_putstr_fd("Error : line ", 2);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(expected_value, 2);
	ft_putstr_fd(" expected\n", 2);
	free_and_quit(fdres);
}
