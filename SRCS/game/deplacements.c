#include "../../includes/cub3d_header.h"

void	go_up(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	aff_screen(game, img_map, BACKGROUND, 2);
	put_map(game, img_map);
	if ((game->map.map[(int)(game->p_x + game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy / game->map.unit) * game->map.width] != 1) && (game->map.map[(int)(game->p_x + game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy / game->map.unit) * game->map.width] != 7))
	{	
		game->p_x += game->p_dx / game->map.unit;
		game->p_y += game->p_dy / game->map.unit;
	}
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	go_down(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	aff_screen(game, img_map, BACKGROUND, 2);
	put_map(game, img_map);
	if ((game->map.map[(int)(game->p_x - game->p_dx / game->map.unit) + (int)(game->p_y - game->p_dy / game->map.unit) * game->map.width] != 1) && (game->map.map[(int)(game->p_x - game->p_dx / game->map.unit) + (int)(game->p_y - game->p_dy / game->map.unit) * game->map.width] != 7))
	{
		game->p_x -= game->p_dx / game->map.unit;
		game->p_y -= game->p_dy / game->map.unit;
	}
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	go_right(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	aff_screen(game, img_map, BACKGROUND, 2);
	put_map(game, img_map);
	if ((game->map.map[(int)(game->p_x - game->p_dy / game->map.unit) + (int)(game->p_y + game->p_dx / game->map.unit) * game->map.width] != 1) && (game->map.map[(int)(game->p_x - game->p_dy / game->map.unit) + (int)(game->p_y + game->p_dx / game->map.unit) * game->map.width] != 7))
	{	
		game->p_x -= game->p_dy / game->map.unit;
		game->p_y += game->p_dx / game->map.unit;
	}
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	go_left(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	aff_screen(game, img_map, BACKGROUND, 2);
	put_map(game, img_map);
	if ((game->map.map[(int)(game->p_x + game->p_dy / game->map.unit) + (int)(game->p_y - game->p_dx / game->map.unit) * game->map.width] != 1) && (game->map.map[(int)(game->p_x + game->p_dy / game->map.unit) + (int)(game->p_y - game->p_dx / game->map.unit) * game->map.width] != 7))
	{	
		game->p_x += game->p_dy / game->map.unit;
		game->p_y -= game->p_dx / game->map.unit;
	}
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}