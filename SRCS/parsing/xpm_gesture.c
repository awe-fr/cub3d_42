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

void	pars_open(t_tmp *tmp)
{
	tmp->northtxt = open("./textures/wall2.xpm", O_RDONLY);
	if (tmp->northtxt == -1)
		printf("Wrong north texture path\n");
	tmp->southtxt = open("./textures/wall.xpm", O_RDONLY);
	if (tmp->southtxt == -1)
		printf("Wrong south texture path\n");
	tmp->easttxt = open("./textures/wall.xpm", O_RDONLY);
	if (tmp->easttxt == -1)
		printf("Wrong east texture path\n");
	tmp->westtxt = open("./textures/wall.xpm", O_RDONLY);
	if (tmp->westtxt == -1)
		printf("Wrong west texture path\n");
	if (tmp->northtxt == -1 || tmp->southtxt == -1
		|| tmp->easttxt == -1 || tmp->westtxt == -1)
	{
		tmp->northtxt = close(tmp->northtxt);
		tmp->southtxt = close(tmp->southtxt);
		tmp->easttxt = close(tmp->easttxt);
		tmp->westtxt = close(tmp->westtxt);
		exit(0);
	}
}

void	check_color(t_tmp *tmp)
{
	if (tmp->north.charactere_per_color > 1)
		printf("North texture to much colorfull\n");
	if (tmp->south.charactere_per_color > 1)
		printf("South texture to much colorfull\n");
	if (tmp->east.charactere_per_color > 1)
		printf("East texture to much colorfull\n");
	if (tmp->west.charactere_per_color > 1)
		printf("West texture to much colorfull\n");
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
		printf("North texture is not a square\n");
	if (tmp->south.width != tmp->south.length)
		printf("South texture is not a square\n");
	if (tmp->east.width != tmp->east.length)
		printf("East texture is not a square\n");
	if (tmp->west.width != tmp->west.length)
		printf("West texture is not a square\n");
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

	pars_open(&tmp);
	tmp.north_xpm = ft_image_to_char(tmp.northtxt);
	tmp.south_xpm = ft_image_to_char(tmp.southtxt);
	tmp.east_xpm = ft_image_to_char(tmp.easttxt);
	tmp.west_xpm = ft_image_to_char(tmp.westtxt);
	tmp.northtxt = close(tmp.northtxt);
	tmp.southtxt = close(tmp.southtxt);
	tmp.easttxt = close(tmp.easttxt);
	tmp.westtxt = close(tmp.westtxt);
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
