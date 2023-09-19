/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srajaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:43:00 by srajaoui          #+#    #+#             */
/*   Updated: 2023/09/19 14:43:01 by srajaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_header.h"

char	*get_line(int xpm, char *buff)
{
	int		str_count;
	char	*buffer;

	buff = malloc(sizeof(char) * 1);
	buff[0] = '\0';
	buffer = malloc(sizeof(char) * 10000 + 2);
	if (!buffer)
		return (NULL);
	str_count = 1;
	buffer[0] = '\0';
	while (str_count != 0)
	{
		str_count = read(xpm, buffer, 10000);
		if (str_count == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[str_count] = '\0';
		buff = ft_strjoin(buff, buffer);
	}
	free(buffer);
	return (buff);
}

char	*cut_line(char *buff)
{
	char	*line;
	int		goodlen;
	int		i;

	goodlen = 0;
	if (buff == NULL)
		return (NULL);
	while (buff[goodlen])
		goodlen++;
	line = malloc(sizeof(char) * (goodlen + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buff[i])
	{
		line[i] = buff[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_flat(int xpm)
{
	char	*xpm_flat;
	char	*buff;

	buff = get_line(xpm, buff);
	if (buff == NULL)
		return (NULL);
	xpm_flat = cut_line(buff);
	free(buff);
	return (xpm_flat);
}

char	**ft_image_to_char(int xpm)
{
	char	**xpm_plan;
	char	*xpm_flat;

	if (xpm < 0)
		exit(0);
	xpm_flat = get_flat(xpm);
	xpm_plan = ft_split(xpm_flat, '\n');
	free(xpm_flat);
	return (xpm_plan);
}
