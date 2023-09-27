/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <srajaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:52:28 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/21 00:52:30 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

void	do_ray(t_game *game)
{
	int	pixel_count;

	set_angle(game);
	game->math.ray = 0;
	pixel_count = 0;
	while (game->math.ray < SCREEN_WIDTH)
	{
		ray_x(game);
		ray_y(game);
		game->math.ray++;
		wich_is_bigger(game);
		were_put_pixel(game);
		angle_correction(game);
		game->math.dis_t = game->math.dis_t * cos(game->math.correction_angle);
		game->math.lineh = (game->map.unit * SCREEN_LENGTH) / game->math.dis_t;
		game->math.lineo = (SCREEN_LENGTH / 2) - game->math.lineh / 2;
		pixel_count = print_line(game, pixel_count);
		game->math.ray_angle += DR / (SCREEN_WIDTH / 66);
		if (game->math.ray_angle < 0)
			game->math.ray_angle += 2 * PI;
		if (game->math.ray_angle > 2 * PI)
			game->math.ray_angle -= 2 * PI;
	}
}
