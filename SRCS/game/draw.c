/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <srajaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:28:33 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/21 01:28:34 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void	gray_screen(t_data *img, int width, int length)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x <= width)
	{
		while (y <= length)
		{
			my_mlx_pixel_put(img, x, y, 9211530);
			y++;
		}
		x++;
		y = 0;
	}
}

void	aff_screen(t_game *game, t_data *img, int code, int size)
{
	int	count_x;
	int	count_y;

	count_y = 0;
	count_x = 0;
	while (count_y != size)
	{
		while (count_x != size)
		{
			my_mlx_pixel_put(img, (game->p_x * 16) + count_x,
				(game->p_y * 16) + count_y, code);
			count_x++;
		}
		count_y++;
		count_x = 0;
	}
}

void	go_wall(int x, int y, t_data *img, int code)
{
	int	count_x;
	int	count_y;

	count_y = 0;
	count_x = 0;
	while (count_y != 16)
	{
		while (count_x != 16)
		{
			my_mlx_pixel_put(img, (x * 16) + count_x,
				(y * 16) + count_y, code);
			count_x++;
		}
		count_y++;
		count_x = 0;
	}
}

void	put_map(t_game *game, t_data *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->map.length)
	{
		while (x < game->map.width)
		{
			if (game->map.map[x + y * game->map.width] == 1)
				go_wall(x, y, img, WALL);
			else if (game->map.map[x + y * game->map.width] == 7)
				go_wall(x, y, img, DOOR_CLOSE);
			else if (game->map.map[x + y * game->map.width] == 6)
				go_wall(x, y, img, DOOR_OPEN);
			x++;
		}
		y++;
		x = 0;
	}
}

void	put_player(t_game *game, t_data *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->map.length)
	{
		while (x < game->map.width)
		{
			if (game->map.map[x + y * game->map.width] == 2)
				go_player(game, x, y, img);
			x++;
		}
		y++;
		x = 0;
	}
}
