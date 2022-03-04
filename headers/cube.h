#ifndef CUBE_H
# define CUBE_H

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
# include <math.h>

enum e_type
{
	NO = 1,
	SO,
	WE,
	EA,
	F,
	C,
	SET,
	GET,
	VERT,
	HOR,
	PLUS,
	MINUS
};

typedef struct s_key
{
	double	olddirx;
	double	oldplanex;
	double	rotspeed;
	double	movespeed;
	double	tmpdirx;
	double	tmpdiry;
}				t_key;

typedef struct s_ray
{
	int		color;
	int		stepx;
	int		stepy;
	int		mapx;
	int		mapy;
	int		hit;
	int		side;
	int		pitch;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		texx;
	int		texy;
	double	posx;
	double	posy;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	double	wallx;
	double	step;
	double	texpos;
}				t_ray;

typedef struct s_plyer
{
	float	x;
	float	y;
	float	orientation;
}				t_plyer;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_plyer	*plyer;
	t_data	*img;
	float	*cast_len;
	char	**map;
	void	*hiero;
	void	*chariot;
	void	*hermit;
	void	*world;
	int		*fd_no;
	int		*fd_so;
	int		*fd_we;
	int		*fd_ea;
	int		floor[3];
	int		ceiling[3];
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}				t_vars;

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

# define S_WIDTH 1200.0
# define S_HEIGHT 700.0
# define CAM_SHIFT 2.0/S_WIDTH
# define UP 122
# define LEFT 113
# define RIGHT 100
# define DOWN 115
# define R_ROT 65363
# define L_ROT 65361
# define XPM_WIDTH 64
# define XPM_HEIGHT 64

void	file_handler(t_fd_read *fdres, char *file_name);

void	free_and_quit(t_fd_read *fdres, int quit);
void	ft_free_char_array(char **char_array);
int		close_img_win(t_vars *var);

void	err_print(t_fd_read *fdres, char *expected_value, int l);
int		end_line_checker(char *line, int l);
int		start_line_checker(char *line, int *j, int l);
int		init_i(char *line, int start);
void	cp_char_array(char ***dest, char **src);
int		empty_line(char *line);
int		authorized_char(char c);
char	*str_char_cat(char *buf, char c);
int		player_set(int status);

int		fill_texture_address_fdres(t_fd_read *fdres, char *line, int i, int l);

void	map_checker(t_fd_read *fdres);

void	first_last_line_checker(t_fd_read *fdres, int i);
void	space_checker(t_fd_read *fdres, int i, int j);
void	map_scanning(t_fd_read *fdres, int i, int j);
void	last_carac_checker(t_fd_read *fdres, int i, int j);
void	first_carac_checker(t_fd_read *fdres, int i);

void	var_plyer_init(t_vars *var, t_fd_read *fdres);
void	initfdres(t_fd_read *fdres);

int		key_press(int key, t_vars *var);
int		render_next_frame(t_vars *var);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_map(t_vars *var);
void	ray_cast(t_vars *var, int index, int vect);
void	draw_vector(t_vars *var, int index, int vect);

int		max_height(int status, int value);
int		max_width(int status, int value);
void	get_textures(t_fd_read *fdres, t_vars *var);

void	cube_drawing(t_vars *var, int x, int y, int color);
void	minimap(t_vars *var);
void	plyrpos(t_vars *var);

int	create_trgb(int t, int r, int g, int b);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);


#endif
