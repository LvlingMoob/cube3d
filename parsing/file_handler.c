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

void	map_checker(t_fd_read *fdres)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (fdres->map[i])
	{
		j = 0;
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
