#include "../includes/cub3d_header.h"

void	go_player(t_game *game, int x, int y, t_data *img)
{
	game->p_x = (float)x + 0.45;
	game->p_y = (float)y + 0.45;
	game->p_a = PI/2;
	game->p_dx = cos(game->p_a) * 5;
	game->p_dy = sin(game->p_a) * 5;
	aff_screen(game, img, PLAYER, 2);
}

void	do_ray(t_game *game, t_data *img)
{
	int r,mx,my,mp,dof; float rx,ry,ra,xo,yo,disT;
	ra = game->p_a - DR * 35;
	if (ra < 0)
		ra += 2 * PI;
	if(ra > 2 * PI)
		ra -= 2 * PI;
	float aTan;
	float nTan;
	float disH, disV, hx, vx, hy, vy;
	float lineH;
	float lineO;
	float ca;
	int z = 0;
	int pixel_count = 0;
	float were_f;
	int were;
	int to_cut;
	r = 0;
	while (r<SCREEN_WIDTH)
	{
		dof = 0;
		disH = 1000000;
		hx = game->p_x * 64;
		hy = game->p_y * 64;
		aTan = -1/tan(ra);
		if (ra>PI)
		{
			ry = (((int)(game->p_y * 64)>>6)<<6) -0.0001;
			rx = ((game->p_y * 64) - ry)*aTan+(game->p_x * 64);
			yo = -64;
			xo = -yo*aTan;
		}
		if (ra<PI)
		{
			ry = (((int)(game->p_y * 64)>>6)<<6) + 64;
			rx = ((game->p_y * 64) - ry)*aTan+(game->p_x * 64);
			yo = 64;
			xo = -yo*aTan;
		}
		if(ra == 0 || ra == PI)
		{
			rx = (game->p_x * 64);
			ry = (game->p_y * 64);
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * game->map.width + mx; 
			if ((mp > 0 && mp<game->map.width*game->map.length && game->map.map[mp] == 1) || (mp > 0 && mp<game->map.width*game->map.length && game->map.map[mp] == 7))
			{
				hx = rx;
				hy = ry;
				disH = dist(game->p_x * 64, game->p_y * 64, hx, hy);
				dof = 8;
			}
			else if ((game->map.map[(int)(game->p_x + game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy / game->map.unit) * game->map.width] != 1) || (game->map.map[(int)(game->p_x + game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy / game->map.unit) * game->map.width] != 7))
			{
				rx+=xo;
				ry+=yo;
				dof+=1;
			}
		}
		dof = 0;
		disV = 1000000;
		vx = game->p_x * 64;
		vy = game->p_y * 64;
		nTan = -tan(ra);
		if (ra>P2 && ra<P3)
		{
			rx = (((int)(game->p_x * 64)>>6)<<6) -0.0001;
			ry = ((game->p_x * 64) - rx)*nTan+(game->p_y * 64);
			xo = -64;
			yo = -xo*nTan;
		}
		if (ra<P2 || ra>P3)
		{
			rx = (((int)(game->p_x * 64)>>6)<<6) + 64;
			ry = ((game->p_x * 64) - rx)*nTan+(game->p_y * 64);
			xo = 64;
			yo = -xo*nTan;
		}
		if(ra == 0 || ra == PI)
		{
			rx = (game->p_x * 64);
			ry = (game->p_y * 64);
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * game->map.width + mx; 
			if ((mp > 0 && mp<game->map.width*game->map.length && game->map.map[mp] == 1) || (mp > 0 && mp<game->map.width*game->map.length && game->map.map[mp] == 7))
			{
				vx = rx;
				vy = ry;
				disV = dist(game->p_x * 64, game->p_y * 64, vx, vy);
				dof = 8;
			}
			else
			{
				rx+=xo;
				ry+=yo;
				dof+=1;
			}
		}
		r++;
		if(disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
		}
		if(disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
		}
		if (ry == vy)
			were_f = (game->p_y + sin(ra) * (disT/64)) - (int)(game->p_y + sin(ra) * (disT/64));
		else
			were_f = (game->p_x + cos(ra) * (disT/64)) - (int)(game->p_x + cos(ra) * (disT/64));
		were = (int)(were_f * game->wall.width);

		ca = game->p_a - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca-= 2 * PI;
		disT = disT * cos(ca);
		// if (r == SCREEN_WIDTH / 2)
		// {
		// 	game->next_wall = disT / 64;
		// 	// printf("%f, %f, %d\n", were_f, game->p_x + cos(ra) * disT/64, (int)(game->p_x + cos(ra) * disT/64));
		// }
		lineH = (game->map.unit * SCREEN_LENGTH) / disT;
		// if (lineH > SCREEN_LENGTH)
		// 	lineH = SCREEN_LENGTH;
		lineO = (SCREEN_LENGTH / 2) - lineH / 2;
	//	if (r == SCREEN_WIDTH / 2)
			//printf("%d\n", (int)(lineH * 64) / 720);
			//printf("%d\n", (int)lineH);
			//to_cut = 720 - lineH;
		while (z < lineH)
		{
			if (z + lineO < 0 || z + lineO > SCREEN_LENGTH)
				z++;
			else if ((were + game->wall.width - (were*2) - 1) >= 0 && (were + game->wall.width - (were*2) - 1) <=  game->wall.width - 1 && ((z * game->wall.width)/(int)lineH) <= game->wall.width - 1 && ((z * game->wall.width)/(int)lineH) >=0 && (ry == vy) && (ra >= PI / 2 && ra <= PI * 1.5))
				my_mlx_pixel_put(img, pixel_count, z + lineO, game->wall.xpm[((z * game->wall.width)/(int)lineH)][were + game->wall.width - (were*2) - 1]);
			// else if (were >= 0 && were <=  game->wall.width - 1 && ((z * game->wall.width)/(int)lineH) <= game->wall.width - 1 && ((z * game->wall.width)/(int)lineH) >=0 && (ry == vy) && (ra < PI / 2 || ra > PI * 1.5))
			// 	my_mlx_pixel_put(img, pixel_count, z + lineO, game->door.xpm[((z * game->wall.width)/(int)lineH)][were]);
			// else if (were >= 0 && were <=  63 && ((z * 64)/(int)lineH) <= 63 && ((z * 64)/(int)lineH) >=0 && (ry == hy) && (ra >= PI))
			// 	my_mlx_pixel_put(img, pixel_count, z + lineO, game->wall.xpm[((z * 64)/(int)lineH)][were]);
			// else if (were >= 0 && were <=  63 && ((z * 64)/(int)lineH) <= 63 && ((z * 64)/(int)lineH) >=0 && (ry == hy) && (ra < PI))
			// 	my_mlx_pixel_put(img, pixel_count, z + lineO, game->door.xpm[((z * 64)/(int)lineH)][were]);
			z++;
		}
		pixel_count++;
		z = 0; 		
		ra += DR / (SCREEN_WIDTH / 70);
		if (ra < 0)
			ra += 2 * PI;
		if(ra > 2 * PI)
			ra -= 2 * PI;
	}
}

int atoi_hexa(char *str)
{
	int result;
	int i;

	result = 0;
	i = 0;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'F'))
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			result += ((str[i] - 55) * pow(16, ft_strlen(str) - i - 1));
		else
			result += ((str[i] - 48) * pow(16, ft_strlen(str) - i - 1));
		i++;
	}
	return (result);
}

int	get_color(t_xpm *xpm, char **xpm_char, int x, int y)
{
	char val;
	int i;
	int z;
	int result;
	char *color;
	int k;

	i = 0;
	z = 4;
	k = 0;
	val = xpm_char[y][x];
	color = malloc(sizeof(char) * 7);
	while ((xpm->colors[i][0] != val) && (xpm->colors[i] != NULL))
		i++;
	while (xpm->colors[i][z] != 0)
	{
		color[k++] = xpm->colors[i][z++];
	}
	result = atoi_hexa(color);
	free(color);
	//printf("%d\n", result);
	return result;
}

void	game_start(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx,SCREEN_WIDTH, SCREEN_LENGTH);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
	game->map.img.img = mlx_new_image(game->map.mlx, game->map.width * 16, game->map.width * 16);
	game->map.img.addr = mlx_get_data_addr(game->map.img.img, &game->map.img.bits_per_pixel, &game->map.img.line_length, &game->map.img.endian);
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	gray_screen(&game->map.img, game->map.width * 16, game->map.length * 16);
	put_map(game, &game->map.img);
	put_player(game, &game->map.img);
	do_ray(game, &game->img);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_hook(game->win, 2, 1L << 0, code_moove, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_moove, game);
}

void	graphic_management(t_game *game)
{
	game->mlx = mlx_init();
	game->map.mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_LENGTH, "cub3d");
	game->map.win = mlx_new_window(game->map.mlx, game->map.width * 16, game->map.width * 16, "minimap");
	mlx_key_hook(game->win, esc_exit, game);
	mlx_hook(game->win, 17, 1L << 8, cross_exit, game);
	game_start(game);
	mlx_loop(game->mlx);
}

int	main(void)
{
	t_game	game;
	
	init_assign(&game);
	int map[] =
	{
		1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,1,
		1,0,2,0,1,0,0,1,
		1,0,0,0,1,0,0,1,
		1,0,0,0,7,0,0,1,
		1,0,1,7,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
	};

	game.map.map = map;
	game.map.width = 8;
	game.map.length = 8;
	game.map.unit = 64;
	graphic_management(&game);
}
