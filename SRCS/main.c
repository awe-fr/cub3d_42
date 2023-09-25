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
	do_ray(game, &game->img);
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

void	all_info(t_game *game, char **map_brut)
{
	int i;
	int count;

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

char	*put_path(t_game *game, char *path_brut)
{
	int i;
	int y;
	char *path;

	i = 0;
	y = 0;
	path = malloc(sizeof(char) * ft_strlen(path_brut) + 1);
	while(path_brut[i] != '.')
		i++;
	while(path_brut[i])
	{
		path[y] = path_brut[i];
		y++;
		i++;
	}
	path[y] = '\0';
	return (path);
}

void	get_texture(t_game *game, char **map_brut)
{
	int i;
	int init;

	i = 0;
	init = 0;
	while (map_brut[i][0] != 'N' && map_brut[i][0] != 'S' &&
			map_brut[i][0] != 'W' && map_brut[i][0] != 'E')
		i++;
	while(init != 4)
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

int	ft_atoi(char *str, int i)
{
	int result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result);
}

int    rgb_to_hex(int r, int g, int b)
{
    return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	get_hexa(t_game *game, char *number)
{
	int i;
	int r;
	int g;
	int b;
	int result;

	i = 0;
	while (!(number[i] >= '0' && number[i] <= '9'))
		i++;
	r = ft_atoi(number, i);
	while(number[i] >= '0' && number[i] <= '9')
		i++;
	while (!(number[i] >= '0' && number[i] <= '9'))
		i++;
	g = ft_atoi(number, i);
	while(number[i] >= '0' && number[i] <= '9')
		i++;
	while (!(number[i] >= '0' && number[i] <= '9'))
		i++;
	b = ft_atoi(number, i);
	if ((b < 0 || b > 255) || (g < 0 || g > 255) || (r < 0 || r > 255))
		return (-1);
	result = rgb_to_hex(r, g, b);
	return (result);
}

void	get_backgroud(t_game *game, char **map_brut)
{
	int i;
	int init;

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
	int i;
	int y;

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

int	map_width(t_game *game, char **map_brut, int start)
{
	int i;
	int count;

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

int	map_length(t_game *game, char **map_brut, int start)
{
	int i;
	int count;
	int stack;

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

char **put_char_map(t_game *game, char **map_brut, int start, char **map_char)
{
	int i;
	int z;
	int c;

	i = -1;
	while (++i != game->map.length)
	{
		c = 0;
		z = 0;
		while (c != game->map.width)
		{
			if(map_brut[start + i][z] && map_brut[start + i][z] != ' ')
				map_char[i][c++] = map_brut[start + i][z];
			else
				map_char[i][c++] = '0';
			if (map_brut[start + i][z])
				z++;
		}
		map_char[i][c] = '\0';
	}
	map_char[i] = NULL;
	return (map_char);
}

void put_in_int(t_game *game, char **map_char)
{
	int *map;
	int i;
	int z;
	int count;

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
			//printf("%d", map[count]);
			count++;
		}
		//printf("\n");
		z = 0;
		i++;
	}
	game->map.map = map;
}

void	get_map(t_game *game, char **map_brut)
{
	int start;
	char **map_char;
	int i;

	i = 0;
	start = were_start(game, map_brut);
	game->map.length = map_length(game, map_brut, start);
	game->map.width = map_width(game, map_brut, start);
	map_char = malloc(sizeof(char *) * (game->map.length + 1));
	while (i != game->map.length)
		map_char[i++] = malloc(sizeof(char) * (game->map.width + 1));
	map_char = put_char_map(game, map_brut, start, map_char);
	//for(int i = 0; map_char[i]; i++){printf("%s\n", map_char[i]);}
	put_in_int(game, map_char);
	free_tab(map_char);
	
}

void	map_verify(t_game *game, char *path)
{
	int map_file;
	char **map_brut;
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
	
	free_tab(map_brut);
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
	// int map[] =
	// {
	// 	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	// 	1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,1,
	// 	1,0,2,0,0,0,0,0,1,0,1,0,0,1,0,1,
	// 	1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
	// 	1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
	// 	1,0,1,0,0,0,0,0,7,0,1,0,0,1,0,1,
	// 	1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,
	// 	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	// 	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	// 	1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
	// 	1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
	// 	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	// 	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	// 	1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,
	// 	1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,
	// 	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	// };

	// game.map.map = map;
	// game.map.width = 16;
	// game.map.length = 16;
	game.map.unit = 64;
	graphic_management(&game);
}
