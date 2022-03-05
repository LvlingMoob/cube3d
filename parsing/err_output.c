#include "cube.h"

void	err_map(t_fd_read *fdres)
{
	ft_putstr_fd("map non conforme\n", 2);
	free_and_quit(fdres, 1);
}
