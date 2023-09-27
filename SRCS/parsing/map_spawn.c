/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_spawn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:16:58 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/27 15:17:01 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void	assign_spawn(t_game *game, char **map_char, int y, int x)
{
	int	count;

	count = 0;
	while (map_char[++y])
	{
		x = 0;
		while (map_char[y][x])
		{
			count += go_set_spawn(game, map_char, y, x);
			x++;
		}
	}
	if (count != 1)
		map_error(game, map_char);
}

int	go_set_spawn(t_game *game, char **map_char, int y, int x)
{
	if (map_char[y][x] == 'N')
	{
		map_char[y][x] = '2';
		game->p_a = P3;
		return (1);
	}
	else if (map_char[y][x] == 'S')
	{
		map_char[y][x] = '2';
		game->p_a = P2;
		return (1);
	}
	return (go_set_spawn_sup(game, map_char, y, x));
}

int	go_set_spawn_sup(t_game *game, char **map_char, int y, int x)
{
	if (map_char[y][x] == 'E')
	{
		map_char[y][x] = '2';
		game->p_a = 0;
		return (1);
	}
	else if (map_char[y][x] == 'W')
	{
		map_char[y][x] = '2';
		game->p_a = PI;
		return (1);
	}
	else if ((map_char[y][x] < '0' || map_char[y][x] > '9')
		&& map_char[y][x] != ' ')
		return (2);
	return (0);
}
