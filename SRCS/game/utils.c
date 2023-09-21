/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <srajaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:47:15 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/21 00:47:22 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int colors)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dest = colors;
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt(((bx - ax) * (bx - ax)) + ((by - ay) * (by - ay))));
}

int	code_moove(int keycode, void *gm)
{
	t_game	*game;

	game = (t_game *)gm;
	if (keycode == 119)
		go_up(game, &game->img, &game->map.img);
	else if (keycode == 115)
		go_down(game, &game->img, &game->map.img);
	else if (keycode == 100)
		go_right(game, &game->img, &game->map.img);
	else if (keycode == 97)
		go_left(game, &game->img, &game->map.img);
	else if (keycode == 101)
		orientation(game, &game->img, &game->map.img);
	else if (keycode == 65363)
		look_right(game, &game->img);
	else if (keycode == 65361)
		look_left(game, &game->img);
	else if (keycode == ESCAPE)
		esc_exit(keycode, game);
	return (0);
}

int	mouse_moove(int mouse_x, int mouse_y, void *gm)
{
	t_game	*game;

	game = (t_game *)gm;
	if (mouse_y >= MOUSE_Y + 100)
		mlx_mouse_move(game->mlx, game->win, MOUSE_X, MOUSE_Y);
	else if (mouse_x >= MOUSE_X + 100)
	{
		mlx_mouse_move(game->mlx, game->win, MOUSE_X, MOUSE_Y);
		look_right(game, &game->img);
	}
	else if (mouse_x <= MOUSE_X -100)
	{
		mlx_mouse_move(game->mlx, game->win, MOUSE_X, MOUSE_Y);
		look_left(game, &game->img);
	}
	else if (mouse_y <= MOUSE_Y - 100)
		mlx_mouse_move(game->mlx, game->win, MOUSE_X, MOUSE_Y);
	return (0);
}

void	go_player(t_game *game, int x, int y, t_data *img)
{
	game->p_x = (float)x + 0.45;
	game->p_y = (float)y + 0.45;
	game->p_a = P2;
	game->p_dx = cos(game->p_a) * 5;
	game->p_dy = sin(game->p_a) * 5;
	aff_screen(game, img, PLAYER, 2);
}
