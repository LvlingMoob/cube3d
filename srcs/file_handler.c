/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:27:47 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 19:27:49 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	max_len_in_array(char **array)
{
	int	i;
	int	tmp;
	int	len;

	i = 0;
	len = 0;
	while (array[i])
	{
		tmp = ft_strlen(array[i]);
		if (tmp > len)
			len = tmp;
		i++;
	}
	return (len);
}

void	norminette_bs(char ***dest, char **src, int *empty, int *max_len)
{
	int	i;

	i = 0;
	(*max_len) = max_len_in_array(src);
	while (empty_line(src[(*empty)]))
		(*empty) += 1;
	while (src[(*empty) + i])
		i++;
	(*dest) = ft_calloc(i + 1, sizeof(char *));
}

void	cp_char_array_with_filler(char ***dest, char **src, int i)
{
	int		diff;
	int		empty;
	int		max_len;
	char	*filler;
	char	*swap;

	norminette_bs(dest, src, &empty, &max_len);
	while (src[empty + i] && !empty_line(src[empty + i]))
	{
		diff = max_len - ft_strlen(src[empty + i]);
		filler = ft_calloc(diff + 1, sizeof(char));
		diff--;
		while (diff >= 0)
		{
			filler[diff] = 32;
			diff--;
		}
		(*dest)[i] = ft_strjoin(src[empty + i], filler);
		free(filler);
		i++;
	}
}

void	init_var_file_checker(char ***content, char **file_content)
{
	*content = ft_split(*file_content, '\n');
	free(*file_content);
}

void	err_on_texture_exit(t_fd_read *fdres, char ***content)
{
	ft_free_char_array(*content);
	free_and_quit(fdres, 1);
}

void	wrong_value_exit(t_fd_read *fdres, char ***content, int l, int i)
{
	ft_free_char_array(*content);
	err_print(fdres, fdres->values[l], i + 1);
}

void	map_cpy_and_free_content(t_fd_read *fdres, char ***content, int i)
{
	cp_char_array_with_filler(&fdres->map, &(*content)[i], 0);
	ft_free_char_array(*content);
}

void	file_checker(t_fd_read *fdres, char **file_content, int i, int l)
{
	int		j;
	char	**content;

	init_var_file_checker(&content, file_content);
	while (content[i] && fdres->values[l])
	{
		j = 0;
		while (content[i][j] && content[i][j] > 0 && content[i][j] <= 32)
			j++;
		if (!content[i][j])
			;
		else if (!(ft_strncmp(fdres->values[l], &content[i][j],
				ft_strlen(fdres->values[l]))))
		{
			if (!fill_texture_address_fdres(fdres, content[i], l, i))
				err_on_texture_exit(fdres, &content);
			l++;
		}
		else
			wrong_value_exit(fdres, &content, l, i);
		i++;
	}
	map_cpy_and_free_content(fdres, &content, i);
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

void	content_rewrite(char **file_content)
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
}

int	file_is_cub(char *file_name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(file_name) - 1;
	while (len + i > 0 && file_name[len + i]
		&& file_name[len + i] != '.')
		i--;
	if (ft_strncmp(&file_name[len + i], ".cub", 4))
		return (0);
	return (1);
}

char	*open_and_read(t_fd_read *fdres, char *file_name)
{
	int		fd;
	char	c;
	char	*file_content;

	file_content = ft_calloc(1, sizeof(char));
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || !file_is_cub(file_name))
	{
		free(file_content);
		printf("%s\n", strerror(errno));
		free_and_quit(fdres, 1);
	}
	while (read(fd, &c, 1) > 0)
		file_content = str_char_cat(file_content, c);
	close(fd);
	return (file_content);
}

void	file_handler(t_fd_read *fdres, char *file_name)
{
	char	*file_content;

	file_content = open_and_read(fdres, file_name);
	content_rewrite(&file_content);
	file_checker(fdres, &file_content, 0, 0);
	map_checker(fdres);
	if (!player_set(GET))
	{
		write(2, "Error : no player set\n", 22);
		free_and_quit(fdres, 1);
	}
}
