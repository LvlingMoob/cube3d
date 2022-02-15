#include "cube.h"

int	fill_var(t_fd_read *fdres, char *line, int i, int l)
{
	static t_lst_check	checker[6] = {
		{0, &final_check_no},
		{1, &final_check_so},
		{2, &final_check_we},
		{3, &final_check_ea},
		{4, &final_check_f},
		{5, &final_check_c}
	};
    
	return ((checker[i].func(fdres, line, l)));
}

int	line_handling(t_fd_read *fdres, char *line, int l)
{
	static int	i = 0;
	int			len;
	int			res;

	res = 0;
	len = ft_strlen(fdres->values[i]);
	if (!(ft_strncmp(fdres->values[i], line, len)))
	{
		res = fill_var(fdres, line, i, l);
		i++;
	}
	else
	{
		printf("line %d : %s expected\n", l, fdres->values[i]);
		free_and_quit(fdres);
	}
	return (res);
}

char	*params_reader(t_fd_read *fdres, int fd, int *line)
{
	int		i;
	char	c;
	char	*buf;

	i = 0;
	buf = ft_calloc(1, sizeof(char));
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			if (!empty_line(buf))
			{
				printf("%s\n", buf);
				i = line_handling(fdres, buf, *line);
			}
			free(buf);
			buf = ft_calloc(1, sizeof(char));
			if (i < 0)
				break ;
			*line += 1;
		}
		else
			buf = str_char_cat(buf, c);
	}
	*line += 1;
	return (buf);
}
