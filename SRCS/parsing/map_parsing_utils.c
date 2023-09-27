/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:15:36 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/27 15:15:38 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

char	*put_path(char *path_brut)
{
	int		i;
	int		y;
	char	*path;

	i = 0;
	y = 0;
	path = malloc(sizeof(char) * ft_strlen(path_brut) + 1);
	while (path_brut[i] != '.')
		i++;
	while (path_brut[i])
	{
		path[y] = path_brut[i];
		y++;
		i++;
	}
	path[y] = '\0';
	return (path);
}

int	get_hexa(char *number)
{
	int	i;
	int	r;
	int	g;
	int	b;
	int	result;

	i = 0;
	while (!(number[i] >= '0' && number[i] <= '9'))
		i++;
	r = ft_atoi(number, i);
	while (number[i] >= '0' && number[i] <= '9')
		i++;
	while (!(number[i] >= '0' && number[i] <= '9'))
		i++;
	g = ft_atoi(number, i);
	while (number[i] >= '0' && number[i] <= '9')
		i++;
	while (!(number[i] >= '0' && number[i] <= '9'))
		i++;
	b = ft_atoi(number, i);
	if ((b < 0 || b > 255) || (g < 0 || g > 255) || (r < 0 || r > 255))
		return (-1);
	result = rgb_to_hex(r, g, b);
	return (result);
}

int	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	ft_atoi(char *str, int i)
{
	int	result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result);
}
