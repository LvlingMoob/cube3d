/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:00:29 by mberengu          #+#    #+#             */
/*   Updated: 2022/03/05 18:00:30 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	err_map(t_fd_read *fdres)
{
	ft_putstr_fd("map non conforme\n", 2);
	free_and_quit(fdres, 1);
}