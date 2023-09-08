#include "../../includes/cub3d_header.h"

void	atoi_for_xpm(char *str, t_xpm *xpm)
{
	int i;
	int result;
	
	i = 0;
	result = 0;
	while (str[++i] != ' ')
		result = result * 10 + (str[i] - 48);
	xpm->width = result;
	result = 0;
	while (str[++i] != ' ')
		result = result * 10 + (str[i] - 48);
	xpm->length = result;
	result = 0;
	while (str[++i] != ' ')
		result = result * 10 + (str[i] - 48);
	xpm->colors_number = result;
	result = 0;
	while (str[++i] != '"')
		result = result * 10 + (str[i] - 48);
	xpm->charactere_per_color = result;
}

void	place_colors(char **xpm_info, t_xpm *xpm)
{
	int x;
	int i;
	int z;

	i = -1;
	x = 0;
	z = 1;
	xpm->colors = malloc(sizeof(char *) * (xpm->colors_number + 1));
	while (++i < xpm->colors_number)
	{
		xpm->colors[i] = malloc(sizeof(char) * 11);
		xpm->colors[i][x++] = xpm_info[i + 3][z++];
		xpm->colors[i][x++] = ' ';
		xpm->colors[i][x++] = '0';
		xpm->colors[i][x++] = 'x';
		while (xpm_info[i + 3][z++] != '#')
		z += 2;
		while (x < 10)
			xpm->colors[i][x++] = xpm_info[i + 3][z++];
		xpm->colors[i][x] = '\0';
		z = 1;
		x = 0;
	}
	xpm->colors[i] = 0;
}

void	xpm_to_char(char **xpm_char, t_xpm *xpm)
{
	int y;
	int x;
	int i;

	y = 3 + xpm->colors_number;
	x = 1;
	i = 0;
	xpm->xpm = malloc(sizeof(char *) * (xpm->length + 1));
	while (xpm_char[y])
	{
		xpm->xpm[i] = malloc(sizeof(char) * (xpm->width + 1));
		while((x - 1) < xpm->width)
		{
			xpm->xpm[i][x - 1] = xpm_char[y][x];
			x++;
		}
		xpm->xpm[i][x - 1] = '\0';
		x = 1;
		y++;
		i++;
	}
	xpm->xpm[i] = 0;
}

void	assign(t_xpm *xpm_struct, char **xpm)
{
	atoi_for_xpm(xpm[2], xpm_struct);
	place_colors(xpm, xpm_struct);
	xpm_to_char(xpm, xpm_struct);
}

void	init_assign(t_game *game)
{
	t_xpm	wall;
	t_xpm	door;
	int walltxt;
	int doortxt;
	
	walltxt = open("./textures/wall.xpm", O_RDONLY);
	char **wall_xpm = ft_image_to_char(walltxt);
	walltxt = close(walltxt);
	assign(&wall, wall_xpm);
	doortxt = open("./textures/door.xpm", O_RDONLY);
	char **door_xpm = ft_image_to_char(doortxt);
	doortxt = close(doortxt);
	assign(&door, door_xpm);
	game->wall = wall;
	game->door = door;
	free_tab(wall_xpm);
	free_tab(door_xpm);
}