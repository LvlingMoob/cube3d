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

void	free_var(t_vars *var)
{
	free(var->plyer);
	ft_free_char_array(var->map);
}

void	free_and_stay(t_fd_read *fdres)
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
