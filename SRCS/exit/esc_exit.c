/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <srajaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:10:48 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/19 03:10:50 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

int	esc_exit(int keycode, t_game *game)
{
	if (keycode == ESCAPE)
		free_graphics(game);
	return (0);
}

int	cross_exit(t_game *game)
{
	free_graphics(game);
	return (0);
}
