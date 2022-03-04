/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:21:53 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/04 20:21:54 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	init_i(char *line, int start)
{
	int	i;

	i = 0;
	if (line[i] > 0 && line[i] <= 32)
	{
		while (line[i] && line[i] > 0 && line[i] <= 32)
			i++;
		i += start;
	}
	else
		i = start;
	return (i);
}

int	start_line_checker(char *line, int *j, int l)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] > 0 && line[i] <= 32))
		i++;
	if (!line[i])
	{
		printf("l %d : %s : error, empty lines\n", l, line);
		return (0);
	}
	*j = i;
	while (line[i] && !(line[i] > 0 && line[i] <= 32))
		i++;
	return (i);
}

int	end_line_checker(char *line, int l)
{
	int	i;

	i = 0;
	if (line[i])
	{
		while (line[i])
		{
			if (!(line[i] > 0 && line[i] <= 32))
			{
				printf("l %d : '%c' : error, unexpected value\n", l, line[i]);
				return (0);
			}
			i++;
		}
	}
	return (1);
}
