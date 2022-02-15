#include "cube.h"

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

void	map_rewrite(t_fd_read *fdres)
{
	int		i;
	int		len_bigger;
	int		len_tmp;

	i = 0;
	len_tmp = 0;
	len_bigger = 0;
	fear_the_non_printable(fdres);
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
	free(*oldbuf);
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

void	parse_cub(t_fd_read *fdres, char *file)
{
	int		i;
	int		fd;
	int		line;
	char	*buf;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	i = 1;
	line = 1;
	buf = params_reader(fdres, fd, &line);
	map_reader(fdres, &buf, fd, line);
	close(fd);
	map_rewrite(fdres);
	map_checker(fdres);
}
