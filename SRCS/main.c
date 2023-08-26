#include "../includes/cub3d_header.h"

void	game_start(t_game *game)
{
	
}

void	graphic_management(void)
{
	t_game	game;
	
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1280, 720, "cub3d");
	mlx_key_hook(game.win, esc_exit, &game);
	mlx_hook(game.win, 17, 1L << 8, cross_exit, &game);
	game_start(&game);
	mlx_loop(game.mlx);
}

int	main(void)
{
	graphic_management();
}
