/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_gesture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:40:28 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/19 14:40:30 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void	pars_open(t_tmp *tmp, t_game *game)
{
	tmp->northtxt = open(game->path_north_xpm, O_RDONLY);
	if (tmp->northtxt == -1)
		printf("Error \nWrong north texture path\n");
	tmp->southtxt = open(game->path_south_xpm, O_RDONLY);
	if (tmp->southtxt == -1)
		printf("Error \nWrong south texture path\n");
	tmp->easttxt = open(game->path_east_xpm, O_RDONLY);
	if (tmp->easttxt == -1)
		printf("Error \nWrong east texture path\n");
	tmp->westtxt = open(game->path_west_xpm, O_RDONLY);
	if (tmp->westtxt == -1)
		printf("Error \nWrong west texture path\n");
	if (tmp->northtxt == -1 || tmp->southtxt == -1
		|| tmp->easttxt == -1 || tmp->westtxt == -1)
	{
		free_path(game);
		free(game->map.map);
		pars_close(tmp);
		exit(0);
	}
}

void	check_color(t_tmp *tmp)
{
	if (tmp->north.charactere_per_color > 1)
		printf("Error \nNorth texture to much colorfull\n");
	if (tmp->south.charactere_per_color > 1)
		printf("Error \nSouth texture to much colorfull\n");
	if (tmp->east.charactere_per_color > 1)
		printf("Error \nEast texture to much colorfull\n");
	if (tmp->west.charactere_per_color > 1)
		printf("Error \nWest texture to much colorfull\n");
	if (tmp->north.charactere_per_color > 1
		|| tmp->south.charactere_per_color > 1
		|| tmp->east.charactere_per_color > 1
		|| tmp->west.charactere_per_color > 1)
	{
		free_tmp_value(tmp);
		exit(0);
	}
}

void	check_square(t_tmp *tmp)
{
	if (tmp->north.width != tmp->north.length)
		printf("Error \nNorth texture is not a square\n");
	if (tmp->south.width != tmp->south.length)
		printf("Error \nSouth texture is not a square\n");
	if (tmp->east.width != tmp->east.length)
		printf("Error \nEast texture is not a square\n");
	if (tmp->west.width != tmp->west.length)
		printf("Error \nWest texture is not a square\n");
	if ((tmp->north.width != tmp->north.length)
		|| (tmp->south.width != tmp->south.length)
		|| (tmp->east.width != tmp->east.length)
		|| (tmp->west.width != tmp->west.length))
	{
		free_tmp_value(tmp);
		exit(0);
	}
}

void	tab_in_xpm(t_tmp *tmp)
{
	place_colors(tmp->north_xpm, &tmp->north);
	place_colors(tmp->south_xpm, &tmp->south);
	place_colors(tmp->east_xpm, &tmp->east);
	place_colors(tmp->west_xpm, &tmp->west);
	xpm_to_int(tmp->north_xpm, &tmp->north);
	xpm_to_int(tmp->south_xpm, &tmp->south);
	xpm_to_int(tmp->east_xpm, &tmp->east);
	xpm_to_int(tmp->west_xpm, &tmp->west);
}

void	init_assign(t_game *game)
{
	t_tmp	tmp;

	pars_open(&tmp, game);
	free(game->path_north_xpm);
	free(game->path_south_xpm);
	free(game->path_east_xpm);
	free(game->path_west_xpm);
	tmp.north_xpm = ft_image_to_char(tmp.northtxt);
	tmp.south_xpm = ft_image_to_char(tmp.southtxt);
	tmp.east_xpm = ft_image_to_char(tmp.easttxt);
	tmp.west_xpm = ft_image_to_char(tmp.westtxt);
	pars_close(&tmp);
	atoi_for_xpm(tmp.north_xpm[2], &tmp.north);
	atoi_for_xpm(tmp.south_xpm[2], &tmp.south);
	atoi_for_xpm(tmp.east_xpm[2], &tmp.east);
	atoi_for_xpm(tmp.west_xpm[2], &tmp.west);
	check_color(&tmp);
	check_square(&tmp);
	tab_in_xpm(&tmp);
	game->north = tmp.north;
	game->south = tmp.south;
	game->east = tmp.east;
	game->west = tmp.west;
	free_tmp_value(&tmp);
}
