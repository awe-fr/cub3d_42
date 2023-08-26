#include "../includes/cub3d_header.h"

int	esc_exit(int keycode, t_game *game)
{
	if (keycode == ESCAPE)
		free_graphics(game);
	return (0);
}

int	cross_exit(t_game *game)
{
	free_graphics(game);
	return (0);
}
