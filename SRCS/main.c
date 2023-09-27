/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <srajaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:31:55 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/21 01:31:57 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_header.h"

void	screen_alloc(t_game *game)
{
	int	y;

	y = 0;
	game->screen = (int **)malloc(sizeof(int *) * SCREEN_LENGTH + 1);
	while (y < SCREEN_LENGTH)
	{
		game->screen[y] = (int *)malloc(sizeof(int) * SCREEN_WIDTH + 1);
		y++;
	}
}

void	game_start(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_LENGTH);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel, &game->img.line_length,
			&game->img.endian);
	game->map.img.img = mlx_new_image(game->map.mlx, game->map.width
			* 16, game->map.width * 16);
	game->map.img.addr = mlx_get_data_addr(game->map.img.img,
			&game->map.img.bits_per_pixel, &game->map.img.line_length,
			&game->map.img.endian);
	gray_screen(&game->map.img, game->map.width * 16, game->map.length * 16);
	put_map(game, &game->map.img);
	put_player(game, &game->map.img);
	do_ray(game);
	tab_to_image(game, &game->img);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_put_image_to_window(game->map.mlx, game->map.win,
		game->map.img.img, 0, 0);
	mlx_hook(game->win, 2, 1L << 0, code_moove, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_moove, game);
}

void	graphic_management(t_game *game)
{
	screen_alloc(game);
	game->mlx = mlx_init();
	game->map.mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_LENGTH, "cub3d");
	game->map.win = mlx_new_window(game->map.mlx, game->map.width
			* 16, game->map.length * 16, "minimap");
	mlx_key_hook(game->win, esc_exit, game);
	mlx_hook(game->win, 17, 1L << 8, cross_exit, game);
	game_start(game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac > 2)
	{
		printf("Error \nTo much map\n");
		return (0);
	}
	if (ac < 2)
	{
		printf("Error \nNo map selected\n");
		return (0);
	}
	map_verify(&game, av[1]);
	init_assign(&game);
	game.map.unit = 64;
	graphic_management(&game);
}
