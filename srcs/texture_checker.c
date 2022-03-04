/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:28:56 by mberengu          #+#    #+#             */
/*   Updated: 2022/02/20 19:28:57 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	digit_value_checker(char *values)
{
	int		i;
	int		coma;

	i = 0;
	coma = 0;
	while (values[i])
	{
		if (values[i] == ',')
			coma++;
		else if (!ft_isdigit(values[i]) && values[i] != 32)
			return (0);
		i++;
	}
	if (coma > 2)
		return (-1);
	return (1);
}

int	final_check_walls(t_fd_read *fdres, char *line, int l, int to_value)
{
	int		i;
	int		j;
	int		strstart;
	char	*tmp;

	i = init_i(line, 2);
	strstart = i;
	i += start_line_checker(&line[i], &j, l);
	if (!end_line_checker(&line[i], l))
		return (0);
	tmp = ft_strdup(&line[strstart + j]);
	if (to_value == NO)
		fdres->no = ft_strtrim(tmp, " ");
	else if (to_value == SO)
		fdres->so = ft_strtrim(tmp, " ");
	else if (to_value == WE)
		fdres->we = ft_strtrim(tmp, " ");
	else if (to_value == EA)
		fdres->ea = ft_strtrim(tmp, " ");
	free(tmp);
	return (1);
}

int	floor_ceiling_digits_value_verif(t_fd_read *fdres, int l, int to_value)
{
	int		ret;
	char	*tmp;

	tmp = NULL;
	if (to_value == F)
		tmp = ft_strdup(fdres->f);
	else if (to_value == C)
		tmp = ft_strdup(fdres->c);
	ret = digit_value_checker(tmp);
	free(tmp);
	if (ret <= 0)
	{
		if (ret < 0)
			printf("l %d : error 3 numbers expected\n", l + 1);
		else if (ret == 0)
			printf("l %d : error, only numbers expected\n", l + 1);
		return (0);
	}
	return (1);
}

int	final_check_floor_ceiling(t_fd_read *fdres, char *line, int l, int to_value)
{
	int	i;
	int	j;
	int	strstart;

	i = init_i(line, 1);
	strstart = i;
	i += start_line_checker(&line[i], &j, l);
	if (!end_line_checker(&line[i], l))
		return (0);
	if (to_value == F)
	{
		fdres->f = ft_strdup(&line[strstart + j]);
		return (floor_ceiling_digits_value_verif(fdres, l, to_value));
	}
	else if (to_value == C)
	{
		fdres->c = ft_strdup(&line[strstart + j]);
		return (floor_ceiling_digits_value_verif(fdres, l, to_value));
	}
	return (0);
}

int	fill_texture_address_fdres(t_fd_read *fdres, char *line, int i, int l)
{
	static t_lst_check	checker[6] = {
	{0, &final_check_walls, NO},
	{1, &final_check_walls, SO},
	{2, &final_check_walls, WE},
	{3, &final_check_walls, EA},
	{4, &final_check_floor_ceiling, F},
	{5, &final_check_floor_ceiling, C}
	};

	return (checker[i].func(fdres, line, l, checker[i].to_value));
}
