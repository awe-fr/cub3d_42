/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_y.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:13:03 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/20 18:13:05 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void ray_y_inforsup(t_game *game)
{
    if (game->math.ray_angle>P2 && game->math.ray_angle<P3)
	{
		game->math.ray_x = (((int)(game->p_x * 64)>>6)<<6) -0.0001;
		game->math.ray_y = ((game->p_x * 64) - game->math.ray_x)
            * game->math.ntan+(game->p_y * 64);
		game->math.x_offset = -64;
		game->math.y_offset = -game->math.x_offset*game->math.ntan;
	}
    if (game->math.ray_angle<P2 || game->math.ray_angle>P3)
	{
		game->math.ray_x = (((int)(game->p_x * 64)>>6)<<6) + 64;
		game->math.ray_y = ((game->p_x * 64) - game->math.ray_x)
            * game->math.ntan+(game->p_y * 64);
		game->math.x_offset = 64;
		game->math.y_offset = -game->math.x_offset*game->math.ntan;
	}
	if(game->math.ray_angle == 0 || game->math.ray_angle == PI)
	{
	    game->math.ray_x = (game->p_x * 64);
		game->math.ray_y = (game->p_y * 64);
		game->math.dof = game->map.width;
	}
}

void were_y(t_game *game)
{
	if ((game->math.map_point > 0 && game->math.map_point < game->map.width
        * game->map.length && game->map.map[game->math.map_point] == 1)
        || (game->math.map_point > 0 && game->math.map_point < game->map.width
        * game->map.length && game->map.map[game->math.map_point] == 7))
	{
		game->math.vertical_x = game->math.ray_x;
		game->math.vertical_y = game->math.ray_y;
		game->math.dis_v = dist(game->p_x * 64, game->p_y * 64,
            game->math.vertical_x, game->math.vertical_y);
		game->math.dof = game->map.width;
	}
	else
	{
		game->math.ray_x+=game->math.x_offset;
		game->math.ray_y+=game->math.y_offset;
		game->math.dof+=1;
	}
}

void ray_y(t_game *game)
{
    game->math.dof = 0;
	game->math.dis_v = 1000000;
	game->math.vertical_x = game->p_x * 64;
	game->math.vertical_y = game->p_y * 64;
	game->math.ntan = -tan(game->math.ray_angle);
	ray_y_inforsup(game);
	while (game->math.dof < game->map.width)
	{
		game->math.map_x = (int)(game->math.ray_x)>>6;
		game->math.map_y = (int)(game->math.ray_y)>>6;
		game->math.map_point = game->math.map_y * game->map.width + game->math.map_x; 
        were_y(game);
	}
}
