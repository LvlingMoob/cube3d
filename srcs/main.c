#include "cube.h"

void	ft_free_char_array(char **char_array)
{
	int		i;

	if (!char_array)
		return ;
	i = 0;
	while (char_array[i])
		free(char_array[i++]);
	free(char_array);
}

void	free_and_quit(t_fd_read *fdres)
{
	int	i;

	i = 0;
	while (fdres->values[i])
	{
		free(fdres->values[i]);
		i++;
	}
	if (fdres->no)
		free(fdres->no);
	if (fdres->so)
		free(fdres->so);
	if (fdres->we)
		free(fdres->we);
	if (fdres->ea)
		free(fdres->ea);
	if (fdres->f)
		free(fdres->f);
	if (fdres->c)
		free(fdres->c);
	free(fdres->values);
	if (fdres->map)
		ft_free_char_array(fdres->map);
	exit(EXIT_FAILURE);
}

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

char	*str_char_cat(char *buf, char c)
{
	size_t	buflen;
	char	*str;
	size_t	i;

	i = 0;
	buflen = ft_strlen(buf);
	str = (char *)ft_calloc((buflen + 2), sizeof(char));
	while (i < buflen)
	{
		str[i] = buf[i];
		i++;
	}
	str[buflen] = c;
	str[buflen + 1] = '\0';
	free(buf);
	return (str);
}

int	empty_line(char *line)
{
	while (*line)
	{
		if (!(*line > 0 && *line <= 32))
			return (0);
		line++;
	}
	return (1);
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

int	pos_player(int status)
{
	static int	player = 0;

	if (status == SET)
		player = 1;
	return (player);
}

int	wrong_char_in_map(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (pos_player(GET))
			return (1);
		pos_player(SET);
	}
	if (c > 0 && c <= 32)
		return (0);
	return (!(c == '0' || c == '1' || c == 'N'
			|| c == 'S' || c == 'E' || c == 'W'));
}

void	first_carac_checker(t_fd_read *fdres, int i)
{
	int	j;

	j = 0;
	while (fdres->map[i][j] && (fdres->map[i][j] > 0 && fdres->map[i][j] <= 32))
		j++;
	if (fdres->map[i][j] != '1')
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

void	last_carac_checker(t_fd_read *fdres, int i, int j)
{
	int	k;

	k = 0;
	while (j - k >= 0 && (fdres->map[i][j - k] > 0 && fdres->map[i][j - k] <= 32))
		k++;
	if (fdres->map[i][j - k] != '1')
		free_and_quit(fdres);
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

char	*space_filler(char **line, int len_bigger)
{
	int		len_tmp;
	int		diff;
	char	*space_filled;
	char	*replacement;

	len_tmp = ft_strlen(*line);
	diff = len_bigger - len_tmp;
	space_filled = ft_calloc(diff + 1, sizeof(char));
	while (--diff >= 0)
		space_filled[diff] = 32;
	replacement = ft_strjoin(*line, space_filled);
	free(*line);
	free(space_filled);
	return (replacement);
}

void	fear_the_number_thirteen(t_fd_read *fdres)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (fdres->map[i])
	{
		j = 0;
		while (fdres->map[i][j])
		{
			if (fdres->map[i][j] == 13)
				fdres->map[i][j] = 32;
			j++;
		}
		i++;
	}
}

void	map_rewrite(t_fd_read *fdres)
{
	int		i;
	int		len_bigger;
	int		len_tmp;
	char	*tmp;

	i = 0;
	len_tmp = 0;
	len_bigger = 0;
	fear_the_number_thirteen(fdres);
	while (fdres->map[i])
	{
		len_tmp = ft_strlen(fdres->map[i]);
		if (len_tmp > len_bigger)
			len_bigger = len_tmp;
		i++;
	}
	i = 0;
	while (fdres->map[i])
	{
		fdres->map[i] = space_filler(&fdres->map[i], len_bigger);
		i++;
	}
}

void	map_reader(t_fd_read *fdres, char **oldbuf, int fd, int line)
{
	int		turn;
	char	*buf;
	char	c;

	if (!empty_line(*oldbuf))
		buf = ft_strdup(*oldbuf);
	else
		buf = ft_calloc(1, sizeof(char));
	turn = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (wrong_char_in_map(c))
		{
			printf("l %d : wrong character %c(%d) detected\n", line, c, c);
			free_and_quit(fdres);
			return ;
		}
		else if (c == '\n')
		{
			if (!empty_line(buf))
			{
				fdres->map = realloc(fdres->map, sizeof(char *) * (turn + 2));
				fdres->map[turn] = ft_strdup(buf);
				fdres->map[turn + 1] = NULL;
				printf("%s\n", fdres->map[turn]);
				turn++;
			}
			free(buf);
			buf = ft_calloc(1, sizeof(char));
			line++;
		}
		else
			buf = str_char_cat(buf, c);
	}
	fdres->map = realloc(fdres->map, sizeof(char *) * (turn + 2));
	fdres->map[turn] = ft_strdup(buf);
	fdres->map[turn + 1] = NULL;
	free(buf);
}

void	cub_file_checker(t_fd_read *fdres, int fd)
{
	int		i;
	int		line;
	char	*buf;

	i = 1;
	line = 1;
	buf = params_reader(fdres, fd, &line);
	map_reader(fdres, &buf, fd, line);
	free(buf);
	map_rewrite(fdres);
	map_checker(fdres);
}

int	str_err(void)
{
	printf("%s\n", strerror(errno));
	exit(1);
}

int	parse_cub(t_fd_read *fdres, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (str_err());
	cub_file_checker(fdres, fd);
	close(fd);
	return (1);
}

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

int	main(int argc, char **argv)
{
	t_fd_read	fdres;

	if (argc != 2)
		return (1);
	initfdres(&fdres);
	parse_cub(&fdres, argv[1]);
	free_and_quit(&fdres);
	return (0);
}
