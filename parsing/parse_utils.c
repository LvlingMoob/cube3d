/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:58:48 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 19:58:49 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
