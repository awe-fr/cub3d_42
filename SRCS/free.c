#include "../includes/cub3d_header.h"
	
void	free_tab(char **tab)
{
	int i;

	i = -1;
	while(tab[++i])
		free(tab[i]);
	free(tab);
}

void	free_graphics(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	mlx_destroy_image(game->map.mlx, game->map.img.img);
	mlx_destroy_window(game->map.mlx, game->map.win);
	mlx_destroy_display(game->map.mlx);
	free(game->map.mlx);
	free_tab(game->wall.xpm);
	free_tab(game->wall.colors);
	free_tab(game->door.xpm);
	free_tab(game->door.colors);
	exit (0);
}