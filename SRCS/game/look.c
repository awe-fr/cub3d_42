/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <srajaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:23:07 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/21 01:23:08 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void	look_left(t_game *game, t_data *img)
{
	game->p_a -= 0.05;
	if (game->p_a < 0)
		game->p_a += 2 * PI;
	game->p_dx = cos(game->p_a) * 5;
	game->p_dy = sin(game->p_a) * 5;
	do_ray(game);
	tab_to_image(game, &game->img);
}

void	look_right(t_game *game, t_data *img)
{
	game->p_a += 0.05;
	if (game->p_a > 2 * PI)
		game->p_a -= 2 * PI;
	game->p_dx = cos(game->p_a) * 5;
	game->p_dy = sin(game->p_a) * 5;
	do_ray(game);
	tab_to_image(game, &game->img);
}

void	orientation(t_game *game, t_data *img, t_data *img_map)
{
	if (game->p_a / PI > 0.25 && game->p_a / PI < 0.75)
		open_south(game, img, img_map);
	else if (game->p_a / PI > 1.25 && game->p_a / PI < 1.75)
		open_north(game, img, img_map);
	else if (game->p_a / PI > 0.75 && game->p_a / PI < 1.25)
		open_west(game, img, img_map);
	else if ((game->p_a / PI > 1.75 && game->p_a / PI <= 1.999999999)
		|| (game->p_a / PI >= 0 && game->p_a / PI < 0.25))
		open_east(game, img, img_map);
}
