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

void	xpm_to_int(char **xpm_char, t_xpm *xpm)
{
	int y;
	int x;
	int i;

	y = 3 + xpm->colors_number;
	x = 1;
	i = 0;
	xpm->xpm = malloc(sizeof(int *) * (xpm->length));
	while(xpm_char[y + i])
	{
		xpm->xpm[i] = malloc(sizeof(int) * (xpm->width));
		while((x - 1) < xpm->width)
		{
			xpm->xpm[i][x - 1] = get_color(xpm, xpm_char, x, y + i);
			x++;
		}
		x = 1;
		i++;			
	}
}

void	pars_open(t_tmp *tmp)
{
	tmp->northtxt = open("./textures/wall.xpm", O_RDONLY);
	if (tmp->northtxt == -1)
		printf("Wrong north texture path\n");
	tmp->southtxt = open("./textures/wall.xpm", O_RDONLY);
	if (tmp->southtxt == -1)
		printf("Wrong south texture path\n");
	tmp->easttxt = open("./textures/wall.xpm", O_RDONLY);
	if (tmp->easttxt == -1)
		printf("Wrong east texture path\n");
	tmp->westtxt = open("./textures/wall.xpm", O_RDONLY);
	if (tmp->westtxt == -1)
		printf("Wrong west texture path\n");
	if (tmp->northtxt == -1 || tmp->southtxt == -1 || tmp->easttxt == -1 || tmp->westtxt == -1)
	{
		tmp->northtxt = close(tmp->northtxt);
		tmp->southtxt = close(tmp->southtxt);
		tmp->easttxt = close(tmp->easttxt);
		tmp->westtxt = close(tmp->westtxt);
		exit(0);
	}
}

void	free_tmp_value(t_tmp *tmp)
{
	free_tab(tmp->north_xpm);
	free_tab(tmp->south_xpm);
	free_tab(tmp->east_xpm);
	free_tab(tmp->west_xpm);
}

void	check_color(t_tmp *tmp)
{
	if (tmp->north.charactere_per_color > 1)
		printf("North texture to much colorfull\n");
	if (tmp->south.charactere_per_color > 1)
		printf("South texture to much colorfull\n");
	if (tmp->east.charactere_per_color > 1)
		printf("East texture to much colorfull\n");
	if (tmp->west.charactere_per_color > 1)
		printf("West texture to much colorfull\n");
	if (tmp->north.charactere_per_color > 1 || tmp->south.charactere_per_color > 1 || tmp->east.charactere_per_color > 1 || tmp->west.charactere_per_color > 1)
	{
		free_tmp_value(tmp);
		exit(0);
	}
}

void	check_square(t_tmp *tmp)
{
	if (tmp->north.width != tmp->north.length)
		printf("North texture is not a square\n");
	if (tmp->south.width != tmp->south.length)
		printf("South texture is not a square\n");
	if (tmp->east.width != tmp->east.length)
		printf("East texture is not a square\n");
	if (tmp->west.width != tmp->west.length)
		printf("West texture is not a square\n");
	if ((tmp->north.width != tmp->north.length) || (tmp->south.width != tmp->south.length) || (tmp->east.width != tmp->east.length) || (tmp->west.width != tmp->west.length))
	{
		free_tmp_value(tmp);
		exit(0);
	}
}

void	init_assign(t_game *game)
{
	t_tmp	tmp;
	t_xpm	north;
	t_xpm	south;
	t_xpm	east;
	t_xpm	west;

	pars_open(&tmp);
	tmp.north_xpm = ft_image_to_char(tmp.northtxt);
	tmp.south_xpm = ft_image_to_char(tmp.southtxt);
	tmp.east_xpm = ft_image_to_char(tmp.easttxt);
	tmp.west_xpm = ft_image_to_char(tmp.westtxt);
	tmp.northtxt = close(tmp.northtxt);
	tmp.southtxt = close(tmp.southtxt);
	tmp.easttxt = close(tmp.easttxt);
	tmp.westtxt = close(tmp.westtxt);
	atoi_for_xpm(tmp.north_xpm[2], &north);
	atoi_for_xpm(tmp.south_xpm[2], &south);
	atoi_for_xpm(tmp.east_xpm[2], &east);
	atoi_for_xpm(tmp.west_xpm[2], &west);
	tmp.north = north;
	tmp.south = south;
	tmp.east = east;
	tmp.west = west;
	check_color(&tmp);
	check_square(&tmp);
	place_colors(tmp.north_xpm, &north);
	place_colors(tmp.south_xpm, &south);
	place_colors(tmp.east_xpm, &east);
	place_colors(tmp.west_xpm, &west);
	xpm_to_int(tmp.north_xpm, &north);
	xpm_to_int(tmp.south_xpm, &south);
	xpm_to_int(tmp.east_xpm, &east);
	xpm_to_int(tmp.west_xpm, &west);
	game->north = north;
	game->south = south;
	game->east = east;
	game->west = west;
	free_tmp_value(&tmp);
}