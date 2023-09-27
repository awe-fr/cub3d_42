/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:15:48 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/27 15:15:51 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void	check_map(t_game *game, char **map_char)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (i != game->map.length)
	{
		while (z != game->map.width)
		{
			if (map_char[i][z] == '0' || map_char[i][z] == '2')
				check_info(game, map_char, i, z);
			z++;
		}
		z = 0;
		i++;
	}
}

void	check_info(t_game *game, char **map_char, int y, int x)
{
	if (y == 0 || x == 0 || y == game->map.length - 1
		|| x == game->map.width - 1)
		map_error(game, map_char);
	if (map_char[y + 1][x] == ' ' || map_char[y + 1][x] == '\0')
		map_error(game, map_char);
	if (map_char[y - 1][x] == ' ' || map_char[y - 1][x] == '\0')
		map_error(game, map_char);
	if (map_char[y][x + 1] == ' ' || map_char[y][x + 1] == '\0')
		map_error(game, map_char);
	if (map_char[y][x - 1] == ' ' || map_char[y][x - 1] == '\0')
		map_error(game, map_char);
	if (map_char[y - 1][x] == '1' && map_char[y][x - 1] == '1'
		&& map_char[y - 1][x - 1] != '1')
		map_error(game, map_char);
	if (map_char[y + 1][x] == '1' && map_char[y][x - 1] == '1'
		&& map_char[y + 1][x - 1] != '1')
		map_error(game, map_char);
	if (map_char[y - 1][x] == '1' && map_char[y][x + 1] == '1'
		&& map_char[y - 1][x + 1] != '1')
		map_error(game, map_char);
	if (map_char[y + 1][x] == '1' && map_char[y][x + 1] == '1'
		&& map_char[y + 1][x + 1] != '1')
		map_error(game, map_char);
}

int	map_length(t_game *game, char **map_brut, int start)
{
	int	i;
	int	count;
	int	stack;

	i = 0;
	count = 0;
	stack = start;
	while (map_brut[start])
	{
		while (map_brut[start][i])
		{
			i++;
			if (map_brut[start][i] == '1')
				count += 1;
		}
		if (count == 0)
			return (start - stack);
		count = 0;
		i = 0;
		start++;
	}
	return (start - stack);
}

int	map_width(t_game *game, char **map_brut, int start)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map_brut[start])
	{
		while (map_brut[start][i])
		{
			i++;
			if (i > count)
				count = i;
		}
		i = 0;
		start++;
	}
	return (count);
}

void	all_info(t_game *game, char **map_brut)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map_brut[i] && map_brut[i][0] != '1' )
	{
		if (map_brut[i][0] == 'N' || map_brut[i][0] == 'S' ||
			map_brut[i][0] == 'W' || map_brut[i][0] == 'E' ||
			map_brut[i][0] == 'C' || map_brut[i][0] == 'F')
			count += 1;
		i++;
	}
	if (count != 6)
	{
		printf("Error\nWrong map info");
		free_tab(map_brut);
		exit(0);
	}
}
