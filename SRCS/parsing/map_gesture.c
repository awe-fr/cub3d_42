/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gesture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:16:20 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/27 15:16:22 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void	get_map(t_game *game, char **map_brut)
{
	int		i;
	int		start;
	char	**map_char;

	i = 0;
	start = were_start(game, map_brut);
	game->map.length = map_length(game, map_brut, start);
	game->map.width = map_width(game, map_brut, start);
	map_char = malloc(sizeof(char *) * (game->map.length + 1));
	while (i != game->map.length)
		map_char[i++] = malloc(sizeof(char) * (game->map.width + 1));
	map_char = put_char_map(game, map_brut, start, map_char);
	free_tab(map_brut);
	assign_spawn(game, map_char, -1, 0);
	check_map(game, map_char);
	put_in_int(game, map_char);
	free_tab(map_char);
}

void	map_verify(t_game *game, char *path)
{
	int		map_file;
	char	**map_brut;

	map_file = open(path, O_RDONLY);
	if (map_file == -1)
	{
		printf("Error \nWrong map path\n");
		exit(0);
	}
	map_brut = ft_image_to_char(map_file);
	map_file = close(map_file);
	all_info(game, map_brut);
	get_texture(game, map_brut);
	get_backgroud(game, map_brut);
	get_map(game, map_brut);
}

char	**put_char_map(t_game *game, char **map_brut, int start \
	, char **map_char)
{
	int	i;
	int	z;
	int	c;

	i = -1;
	while (++i != game->map.length)
	{
		c = 0;
		z = 0;
		while (c != game->map.width)
		{
			if (map_brut[start + i][z] && map_brut[start + i][z] != ' ')
				map_char[i][c++] = map_brut[start + i][z];
			else
				map_char[i][c++] = ' ';
			if (map_brut[start + i][z])
				z++;
		}
		map_char[i][c] = '\0';
	}
	map_char[i] = NULL;
	return (map_char);
}

void	put_in_int(t_game *game, char **map_char)
{
	int	*map;
	int	i;
	int	z;
	int	count;

	i = 0;
	z = 0;
	count = 0;
	map = malloc(sizeof(int) * (game->map.width * game->map.length));
	while (i != game->map.length)
	{
		while (z != game->map.width)
		{
			if (map_char[i][z] == 'N')
				map[count] = 2;
			else
				map[count] = map_char[i][z] - 48;
			z++;
			count++;
		}
		z = 0;
		i++;
	}
	game->map.map = map;
}

void	map_error(t_game *game, char **map_char)
{
	free_tab(map_char);
	free(game->path_east_xpm);
	free(game->path_west_xpm);
	free(game->path_south_xpm);
	free(game->path_north_xpm);
	printf("Error\nMap problem\n");
	exit(0);
}
