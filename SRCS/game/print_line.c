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

void	were_put_pixel(t_game *game)
{
	if (game->math.ray_y == game->math.vertical_y)
		game->math.were_f = (game->p_y + sin(game->math.ray_angle)
				* (game->math.dis_t / 64)) - (int)(game->p_y
				+ sin(game->math.ray_angle) * (game->math.dis_t / 64));
	else
		game->math.were_f = (game->p_x + cos(game->math.ray_angle)
				* (game->math.dis_t / 64)) - (int)(game->p_x
				+ cos(game->math.ray_angle) * (game->math.dis_t / 64));
	game->math.weren = (int)(game->math.were_f * game->north.width);
	game->math.weree = (int)(game->math.were_f * game->east.width);
	game->math.werew = (int)(game->math.were_f * game->west.width);
	game->math.weres = (int)(game->math.were_f * game->south.width);
}

void	tab_to_image(t_game *game, t_data *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < SCREEN_LENGTH)
	{
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(img, x, y, game->screen[y][x]);
			x++;
		}
		y++;
		x = 0;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
