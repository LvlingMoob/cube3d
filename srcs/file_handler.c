#include "cube.h"

void	file_checker(t_fd_read *fdres, char **file_content, int i, int l)
{
	int		j;
	char	**content;

	content = ft_split(*file_content, '\n');
	free(*file_content);
	while (content[i] && fdres->values[l])
	{
		j = 0;
		if (empty_line(content[i]))
		{
			i++;
			continue ;
		}
		while (content[i][j] && content[i][j] > 0 && content[i][j] <= 32)
			j++;
		if (!(ft_strncmp(fdres->values[l], &content[i][j],
			ft_strlen(fdres->values[l]))))
		{
			if (!fill_texture_address_fdres(fdres, content[i], l, i))
			{
				ft_free_char_array(content);
				free_and_quit(fdres, 1);
			}
			l++;
		}
		else
		{
			ft_free_char_array(content);
			err_print(fdres, fdres->values[l], i + 1);
		}
		i++;
	}
	cp_char_array(&fdres->map, &content[i]);
	ft_free_char_array(content);
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

int	content_rewrite(char **file_content)
{
	int	i;

	i = 0;
	while ((*file_content)[i])
	{
		if ((*file_content)[i] > 0 && (*file_content)[i] < 32
			&& (*file_content)[i] != '\n')
			(*file_content)[i] = 32;
		i++;
	}
	return (1);
}

void	file_handler(t_fd_read *fdres, char *file_name)
{
	int		fd;
	char	c;
	char	*file_content;

	file_content = ft_calloc(1, sizeof(char));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	while (read(fd, &c, 1) > 0)
		file_content = str_char_cat(file_content, c);
	close(fd);
	if (!content_rewrite(&file_content))
	{
		free(file_content);
		free_and_quit(fdres, 1);
	}
	file_checker(fdres, &file_content, 0, 0);
	map_checker(fdres);
	if (!player_set(GET))
	{
		write(2, "Error : no player set\n", 22);
		free_and_quit(fdres, 1);
	}
}
