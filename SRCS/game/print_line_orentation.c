/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line_orentation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:57:12 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/20 16:57:14 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void	print_texture_north(t_game *game, int pixel_count, int z, int gray)
{
	int		weren;
	int		n_width;
	int		lineh;
	int		lineo;
	float	ra;

	weren = game->math.weren;
	n_width = game->north.width;
	lineh = (int)game->math.lineh;
	lineo = (int)game->math.lineo;
	ra = game->math.ray_angle;
	if ((weren) >= 0 && (weren <= n_width - 1) && ((z * n_width) / lineh)
		<= n_width - 1 && ((z * n_width) / lineh) >= 0 && (game->math.ray_y
			== game->math.horizontal_y) && (ra >= PI))
		game->screen[z + lineo][pixel_count] = game->north.xpm[((z * n_width)
				/ lineh)][weren];
}

void	print_texture_south(t_game *game, int pixel_count, int z, int gray)
{
	int		weres;
	int		s_width;
	int		lineh;
	int		lineo;
	float	ra;

	weres = game->math.weres;
	s_width = game->south.width;
	lineh = (int)game->math.lineh;
	lineo = (int)game->math.lineo;
	ra = game->math.ray_angle;
	if ((weres + s_width - (weres * 2) - 1) >= 0 && (weres + s_width - (weres
				* 2) - 1) <= s_width - 1 && ((z * s_width) / lineh) <= s_width
		- 1 && ((z * s_width) / lineh) >= 0 && (game->math.ray_y
			== game->math.horizontal_y) && (ra < PI))
		game->screen[z + lineo][pixel_count] = game->south.xpm[((z * s_width)
				/ lineh)][weres + s_width - (weres * 2) - 1];
	else
		print_texture_north(game, pixel_count, z, gray);
}

void	print_texture_east(t_game *game, int pixel_count, int z, int gray)
{
	int		weree;
	int		e_width;
	int		lineh;
	int		lineo;
	float	ra;

	weree = game->math.weree;
	e_width = game->east.width;
	lineh = (int)game->math.lineh;
	lineo = (int)game->math.lineo;
	ra = game->math.ray_angle;
	if ((weree) >= 0 && (weree <= e_width - 1) && ((z * e_width) / lineh)
		<= e_width - 1 && ((z * e_width) / lineh) >= 0 && (game->math.ray_y
			== game->math.vertical_y) && (ra < P2 || ra > P3))
		game->screen[z + lineo][pixel_count]
			= game->east.xpm[((z * e_width) / lineh)][weree];
	else
		print_texture_south(game, pixel_count, z, gray);
}

void	print_texture_west(t_game *game, int pixel_count, int z, int gray)
{
	int		werew;
	int		w_width;
	int		lineh;
	int		lineo;
	float	ra;

	werew = game->math.werew;
	w_width = game->west.width;
	lineh = (int)game->math.lineh;
	lineo = (int)game->math.lineo;
	ra = game->math.ray_angle;
	if ((werew + w_width - (werew * 2) - 1) >= 0 && (werew + w_width - (werew
				* 2) - 1) <= w_width - 1 && ((z * w_width) / lineh) <= w_width
		- 1 && ((z * w_width) / lineh) >= 0 && (game->math.ray_y
			== game->math.vertical_y) && (ra >= P2 && ra <= P3))
		game->screen[z + lineo][pixel_count] = game->west.xpm[((z * w_width)
				/ lineh)][werew + w_width - (werew * 2) - 1];
	else
		print_texture_east(game, pixel_count, z, gray);
}
