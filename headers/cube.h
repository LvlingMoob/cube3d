#ifndef CUBE_H
#define CUBE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

enum e_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	SET,
	GET
};

typedef struct s_fd_read
{
	char	**values;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	char	**map;
}				t_fd_read;

typedef struct s_lst_check
{
	int		index;
	int	(*func)(t_fd_read *fdres, char *line, int l);
}				t_lst_check;

#endif
