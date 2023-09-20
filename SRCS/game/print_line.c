/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:34:02 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/20 16:34:04 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

int	print_sky(t_game *game, int pixel_count, int z, int gray)
{
	gray = 0;
	while (game->math.lineh - SCREEN_LENGTH + (gray * 2) < 0)
	{
		game->screen[gray][pixel_count] = 9211530;
		gray++;
	}
	return (gray);
}

void	print_floor(t_game *game, int pixel_count, int z, int gray)
{
	gray -= 2;
	while (gray < 720)
	{
		game->screen[gray][pixel_count] = 9211530;
		gray++;
	}
}

int	print_line(t_game *game, int pixel_count)
{
	int	gray;
	int	z;

	z = 0;
	gray = print_sky(game, pixel_count, z, gray);
	while (z < game->math.lineh)
	{
		if (z + (int)game->math.lineo < 0 || z
			+ (int)game->math.lineo > SCREEN_LENGTH - 1)
			z = z;
		else
			print_texture_west(game, pixel_count, z, gray);
		z++;
		gray++;
	}
	print_floor(game, pixel_count, z, gray);
	pixel_count++;
	return (pixel_count);
}
