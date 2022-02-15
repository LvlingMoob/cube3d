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

typedef struct s_vars {
	void	*mlx;
	void	*win;
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
	int	(*func)(t_fd_read *fdres, char *line, int l);
}				t_lst_check;



int		key_hook(int key, t_vars *var);
int		close_img_win(t_vars *var);


void	parse_cub(t_fd_read *fdres, char *file);
void	map_checker(t_fd_read *fdres);

// free stuff
void	free_and_quit(t_fd_read *fdres);
void	ft_free_char_array(char **char_array);

// globals
int		pos_player(int status);

// checker
int	final_check_c(t_fd_read *fdres, char *line, int l);
int	final_check_f(t_fd_read *fdres, char *line, int l);
int	final_check_ea(t_fd_read *fdres, char *line, int l);
int	final_check_we(t_fd_read *fdres, char *line, int l);
int	final_check_so(t_fd_read *fdres, char *line, int l);
int	final_check_no(t_fd_read *fdres, char *line, int l);
int	digit_value_checker(t_fd_read *fdres, char *values, int l);
void	end_line_checker(t_fd_read *fdres, char *line, int l);
int	start_line_checker(t_fd_read *fdres, char *line, int *j, int l);
void	map_checker(t_fd_read *fdres);

//utils
void	initfdres(t_fd_read *fdres);
char	*str_char_cat(char *buf, char c);
int		empty_line(char *line);
void	fear_the_non_printable(t_fd_read *fdres);
int		wrong_char_in_map(char c);

//params reader
char	*params_reader(t_fd_read *fdres, int fd, int *line);

#endif
