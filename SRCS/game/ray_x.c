/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:12:57 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/20 18:12:59 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void	ray_x_inforsup(t_game *game)
{
	if (game->math.ray_angle > PI)
	{
		game->math.ray_y = (((int)(game->p_y * 64) >> 6) << 6) - 0.0001;
		game->math.ray_x = ((game->p_y * 64) - game->math.ray_y)
			* game->math.atan + (game->p_x * 64);
		game->math.y_offset = -64;
		game->math.x_offset = -game->math.y_offset * game->math.atan;
	}
	if (game->math.ray_angle < PI)
	{
		game->math.ray_y = (((int)(game->p_y * 64) >> 6) << 6) + 64;
		game->math.ray_x = ((game->p_y * 64) - game->math.ray_y)
			* game->math.atan + (game->p_x * 64);
		game->math.y_offset = 64;
		game->math.x_offset = -game->math.y_offset * game->math.atan;
	}
	if (game->math.ray_angle == 0 || game->math.ray_angle == PI)
	{
		game->math.ray_x = (game->p_x * 64);
		game->math.ray_y = (game->p_y * 64);
		game->math.dof = game->map.length;
	}
}

void	were_x(t_game *game)
{
	if ((game->math.map_point > 0 && game->math.map_point < game->map.width
			* game->map.length && game->map.map[game->math.map_point] == 1)
		|| (game->math.map_point > 0 && game->math.map_point < game->map.width
			* game->map.length && game->map.map[game->math.map_point] == 7))
	{
		game->math.horizontal_x = game->math.ray_x;
		game->math.horizontal_y = game->math.ray_y;
		game->math.dis_h = dist(game->p_x * 64, game->p_y * 64,
				game->math.horizontal_x, game->math.horizontal_y);
		game->math.dof = game->map.length;
	}
	else if ((game->map.map[(int)(game->p_x + game->p_dx / game->map.unit)
			+ (int)(game->p_y + game->p_dy / game->map.unit)
		* game->map.width] != 1) || (game->map.map[(int)(game->p_x
			+ game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy
			/ game->map.unit) * game->map.width] != 7))
	{
		game->math.ray_x += game->math.x_offset;
		game->math.ray_y += game->math.y_offset;
		game->math.dof += 1;
	}
}

void	ray_x(t_game *game)
{
	game->math.dof = 0;
	game->math.dis_h = 1000000;
	game->math.horizontal_x = game->p_x * 64;
	game->math.horizontal_y = game->p_y * 64;
	game->math.atan = -1 / tan(game->math.ray_angle);
	ray_x_inforsup(game);
	while (game->math.dof < game->map.length)
	{
		game->math.map_x = (int)(game->math.ray_x) >> 6;
		game->math.map_y = (int)(game->math.ray_y) >> 6;
		game->math.map_point = game->math.map_y * game->map.width
			+ game->math.map_x;
		were_x(game);
	}
}

void	wich_is_bigger(t_game *game)
{
	if (game->math.dis_v < game->math.dis_h)
	{
		game->math.ray_x = game->math.vertical_x;
		game->math.ray_y = game->math.vertical_y;
		game->math.dis_t = game->math.dis_v;
	}
	if (game->math.dis_h < game->math.dis_v)
	{
		game->math.ray_x = game->math.horizontal_x;
		game->math.ray_y = game->math.horizontal_y;
		game->math.dis_t = game->math.dis_h;
	}
}

void	angle_correction(t_game *game)
{
		game->math.correction_angle = game->p_a - game->math.ray_angle;
	if (game->math.correction_angle < 0)
		game->math.correction_angle += 2 * PI;
	if (game->math.correction_angle > 2 * PI)
		game->math.correction_angle -= 2 * PI;
}
