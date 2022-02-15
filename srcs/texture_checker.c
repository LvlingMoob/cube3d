#include "cube.h"

int	start_line_checker(t_fd_read *fdres, char *line, int *j, int l)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] > 0 && line[i] <= 32))
		i++;
	if (!line[i])
	{
		printf("l %d : %s : error, unexpected value\n", l, line);
		free_and_quit(fdres);
	}
	*j = i;
	while (line[i] && !(line[i] > 0 && line[i] <= 32))
		i++;
	return (i);
}

void	end_line_checker(t_fd_read *fdres, char *line, int l)
{
	int	i;

	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (!(line[i] > 0 && line[i] <= 32))
		{
			printf("l %d : %s : error, unexpected value\n", l, line);
			free_and_quit(fdres);
		}
		i++;
	}
}

int	final_check_no(t_fd_read *fdres, char *line, int l)
{
	int	i;
	int	j;

	i = 2;
	i += start_line_checker(fdres, &line[i], &j, l);
	end_line_checker(fdres, &line[i], l);
	fdres->no = ft_strdup(&line[2 + j]);
	return (1);
}

int	final_check_so(t_fd_read *fdres, char *line, int l)
{
	int	i;
	int	j;

	i = 2;
	i += start_line_checker(fdres, &line[i], &j, l);
	end_line_checker(fdres, &line[i], l);
	fdres-> so = ft_strdup(&line[2 + j]);
	return (1);
}

int	final_check_we(t_fd_read *fdres, char *line, int l)
{
	int	i;
	int	j;

	i = 2;
	i += start_line_checker(fdres, &line[i], &j, l);
	end_line_checker(fdres, &line[i], l);
	fdres->we = ft_strdup(&line[2 + j]);
	return (1);
}

int	final_check_ea(t_fd_read *fdres, char *line, int l)
{
	int	i;
	int	j;

	i = 2;
	i += start_line_checker(fdres, &line[i], &j, l);
	end_line_checker(fdres, &line[i], l);
	fdres->ea = ft_strdup(&line[2 + j]);
	return (1);
}

int	final_check_f(t_fd_read *fdres, char *line, int l)
{
	int		i;
	int		j;

	i = 1;
	i += start_line_checker(fdres, &line[i], &j, l);
	end_line_checker(fdres, &line[i], l);
	fdres->f = ft_strdup(&line[1 + j]);
	if (!digit_value_checker(fdres, fdres->f, l))
	{
		printf("l %d : %s : error, numbers expected\n", l, line);
		free_and_quit(fdres);
	}
	return (1);
}

int	final_check_c(t_fd_read *fdres, char *line, int l)
{
	int	i;
	int	j;

	i = 1;
	i += start_line_checker(fdres, &line[i], &j, l);
	end_line_checker(fdres, &line[i], l);
	fdres-> c = ft_strdup(&line[1 + j]);
	if (!digit_value_checker(fdres, fdres->c, l))
	{
		printf("l %d : %s : error, numbers expected\n", l, line);
		free_and_quit(fdres);
	}
	return (-1);
}
