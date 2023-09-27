/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:16:06 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/27 15:16:10 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void	get_texture(t_game *game, char **map_brut)
{
	int	i;
	int	init;

	i = 0;
	init = 0;
	while (map_brut[i][0] != 'N' && map_brut[i][0] != 'S' &&
			map_brut[i][0] != 'W' && map_brut[i][0] != 'E')
		i++;
	while (init != 4)
	{
		if (map_brut[i][0] == 'N')
			game->path_north_xpm = put_path(game, map_brut[i]);
		if (map_brut[i][0] == 'S')
			game->path_south_xpm = put_path(game, map_brut[i]);
		if (map_brut[i][0] == 'W')
			game->path_east_xpm = put_path(game, map_brut[i]);
		if (map_brut[i][0] == 'E')
			game->path_west_xpm = put_path(game, map_brut[i]);
		i++;
		init++;
	}
}

void	get_backgroud(t_game *game, char **map_brut)
{
	int	i;
	int	init;

	i = 0;
	init = 0;
	game->ceiling = -1;
	game->floor = -1;
	while (map_brut[i][0] != 'F' && map_brut[i][0] != 'C')
		i++;
	while (init != 2)
	{
		if (map_brut[i][0] == 'F')
			game->floor = get_hexa(game, map_brut[i++]);
		if (map_brut[i][0] == 'C')
			game->ceiling = get_hexa(game, map_brut[i++]);
		if (game->ceiling == -1 || game->floor == -1)
		{
			printf("Error\nWrong color\n");
			free_tab(map_brut);
			free_path(game);
			exit(0);
		}
		init++;
	}
}

int	were_start(t_game *game, char **map_brut)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (map_brut[y])
	{
		while (map_brut[y][i])
		{
			if (map_brut[y][i] == '1' && map_brut[y][0] != 'N'
				&& map_brut[y][0] != 'S' && map_brut[y][0] != 'E'
				&& map_brut[y][0] != 'W' && map_brut[y][0] != 'C'
				&& map_brut[y][0] != 'F')
				return (y);
			i++;
		}
		i = 0;
		y++;
	}
	printf("Error\nNo map in map file\n");
	free_tab(map_brut);
	free_path(game);
	exit(0);
}
