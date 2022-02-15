#include "cube.h"

int	pos_player(int status)
{
	static int	player = 0;

	if (status == SET)
		player = 1;
	return (player);
}
