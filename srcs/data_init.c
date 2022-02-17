#include "cube.h"

// void	plyer_map_init(t_vars *var, t_fd_read *fdres)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		l;
// 	int		sixty_four;
// 	char	*tmp;

// 	i = 0;
// 	while (fdres->map[i])
// 		i++;
// 	var->map = ft_calloc((i * 64) + 1, sizeof(char *));
// 	i = 0;
// 	l = 0;
// 	tmp = ft_calloc(1, sizeof(char));
// 	while (fdres->map[i])
// 	{
// 		j = 0;
// 		k = 0;
// 		while (fdres->map[i][j])
// 		{
// 			tmp[k] = str_char_cat(tmp, fdres->map[i][j])
// 			k++;
// 			if (!(k % 64))
// 				j++;
// 		}
// 		sixty_four = 0;
// 		while (sixty_four < 64)
// 		{
// 			var->map[l] = ft_strdup(tmp);
// 			l++;
// 			sixty_four++;
// 		}
// 		free(tmp);
// 		i++;
// 	}
// 	for (int rows = 0; var->map[rows]; rows ++)
// 		printf("%s\n", var->map[rows]);
// }