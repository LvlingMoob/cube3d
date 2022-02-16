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
# include <mlx.h>

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

typedef struct	s_plyer
{
	int		x;
	int		y;
	float	orientation;
}				t_plyer;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_plyer	*plyer;
	char	**map;
	int		fd_no;
	int		fd_so;
	int		fd_we;
	int		fd_ea;
	int		floor[3];
	int		ceiling[3];
}				t_vars;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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
	int		(*func)(t_fd_read *fdres, char *line, int l, int to_value);
	int		to_value;
}				t_lst_check;




void	file_handler(t_fd_read *fdres, char *file_name);

void	free_and_quit(t_fd_read *fdres);
void	ft_free_char_array(char **char_array);


void	err_print(t_fd_read *fdres, char *expected_value, int l);
int		end_line_checker(char *line, int l);
int		start_line_checker(char *line, int *j, int l);
int		init_i(char *line, int start);


int	fill_texture_address_fdres(t_fd_read *fdres, char *line, int i, int l);

void	map_checker(t_fd_read *fdres);

#endif
