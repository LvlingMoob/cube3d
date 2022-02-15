#include "cube.h"

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

void	fear_the_non_printable(t_fd_read *fdres)
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
			if (fdres->map[i][j] > 0 && fdres->map[i][j] < 32)
				fdres->map[i][j] = 32;
			j++;
		}
		i++;
	}
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
