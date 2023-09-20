#include "../includes/cub3d_header.h"

void	go_player(t_game *game, int x, int y, t_data *img)
{
	game->p_x = (float)x + 0.45;
	game->p_y = (float)y + 0.45;
	game->p_a = PI;
	game->p_dx = cos(game->p_a) * 5;
	game->p_dy = sin(game->p_a) * 5;
	aff_screen(game, img, PLAYER, 2);
}

void	do_ray(t_game *game, t_data *img)
{
	game->math.ray_angle = game->p_a - DR * 33;
	if (game->math.ray_angle < 0)
		game->math.ray_angle += 2 * PI;
	if(game->math.ray_angle > 2 * PI)
		game->math.ray_angle -= 2 * PI;
	game->math.ray = 0;
	int z = 0;
	int pixel_count = 0;
	int gray;
	gray = 0;
	while (game->math.ray<SCREEN_WIDTH)
	{
		game->math.dof = 0;
		game->math.disH = 1000000;
		game->math.horizontal_x = game->p_x * 64;
		game->math.horizontal_y = game->p_y * 64;
		game->math.aTan = -1/tan(game->math.ray_angle);
		if (game->math.ray_angle>PI)
		{
			game->math.ray_y = (((int)(game->p_y * 64)>>6)<<6) -0.0001;
			game->math.ray_x = ((game->p_y * 64) - game->math.ray_y)*game->math.aTan+(game->p_x * 64);
			game->math.y_offset = -64;
			game->math.x_offset = -game->math.y_offset*game->math.aTan;
		}
		if (game->math.ray_angle<PI)
		{
			game->math.ray_y = (((int)(game->p_y * 64)>>6)<<6) + 64;
			game->math.ray_x = ((game->p_y * 64) - game->math.ray_y)*game->math.aTan+(game->p_x * 64);
			game->math.y_offset = 64;
			game->math.x_offset = -game->math.y_offset*game->math.aTan;
		}
		if(game->math.ray_angle == 0 || game->math.ray_angle == PI)
		{
			game->math.ray_x = (game->p_x * 64);
			game->math.ray_y = (game->p_y * 64);
			game->math.dof = game->map.length;
		}
		while (game->math.dof < game->map.length)
		{
			game->math.map_x = (int)(game->math.ray_x)>>6;
			game->math.map_y = (int)(game->math.ray_y)>>6;
			game->math.map_point = game->math.map_y * game->map.width + game->math.map_x; 
			if ((game->math.map_point > 0 && game->math.map_point<game->map.width*game->map.length && game->map.map[game->math.map_point] == 1) || (game->math.map_point > 0 && game->math.map_point<game->map.width*game->map.length && game->map.map[game->math.map_point] == 7))
			{
				game->math.horizontal_x = game->math.ray_x;
				game->math.horizontal_y = game->math.ray_y;
				game->math.disH = dist(game->p_x * 64, game->p_y * 64, game->math.horizontal_x, game->math.horizontal_y);
				game->math.dof = game->map.length;
			}
			else if ((game->map.map[(int)(game->p_x + game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy / game->map.unit) * game->map.width] != 1) || (game->map.map[(int)(game->p_x + game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy / game->map.unit) * game->map.width] != 7))
			{
				game->math.ray_x+=game->math.x_offset;
				game->math.ray_y+=game->math.y_offset;
				game->math.dof+=1;
			}
		}
		game->math.dof = 0;
		game->math.disV = 1000000;
		game->math.vertical_x = game->p_x * 64;
		game->math.vertical_y = game->p_y * 64;
		game->math.nTan = -tan(game->math.ray_angle);
		if (game->math.ray_angle>P2 && game->math.ray_angle<P3)
		{
			game->math.ray_x = (((int)(game->p_x * 64)>>6)<<6) -0.0001;
			game->math.ray_y = ((game->p_x * 64) - game->math.ray_x)*game->math.nTan+(game->p_y * 64);
			game->math.x_offset = -64;
			game->math.y_offset = -game->math.x_offset*game->math.nTan;
		}
		if (game->math.ray_angle<P2 || game->math.ray_angle>P3)
		{
			game->math.ray_x = (((int)(game->p_x * 64)>>6)<<6) + 64;
			game->math.ray_y = ((game->p_x * 64) - game->math.ray_x)*game->math.nTan+(game->p_y * 64);
			game->math.x_offset = 64;
			game->math.y_offset = -game->math.x_offset*game->math.nTan;
		}
		if(game->math.ray_angle == 0 || game->math.ray_angle == PI)
		{
			game->math.ray_x = (game->p_x * 64);
			game->math.ray_y = (game->p_y * 64);
			game->math.dof = game->map.width;
		}
		while (game->math.dof < game->map.width)
		{
			game->math.map_x = (int)(game->math.ray_x)>>6;
			game->math.map_y = (int)(game->math.ray_y)>>6;
			game->math.map_point = game->math.map_y * game->map.width + game->math.map_x; 
			if ((game->math.map_point > 0 && game->math.map_point<game->map.width*game->map.length && game->map.map[game->math.map_point] == 1) || (game->math.map_point > 0 && game->math.map_point<game->map.width*game->map.length && game->map.map[game->math.map_point] == 7))
			{
				game->math.vertical_x = game->math.ray_x;
				game->math.vertical_y = game->math.ray_y;
				game->math.disV = dist(game->p_x * 64, game->p_y * 64, game->math.vertical_x, game->math.vertical_y);
				game->math.dof = game->map.width;
			}
			else
			{
				game->math.ray_x+=game->math.x_offset;
				game->math.ray_y+=game->math.y_offset;
				game->math.dof+=1;
			}
		}
		game->math.ray++;
		if(game->math.disV < game->math.disH)
		{
			game->math.ray_x = game->math.vertical_x;
			game->math.ray_y = game->math.vertical_y;
			game->math.disT = game->math.disV;
		}
		if(game->math.disH < game->math.disV)
		{
			game->math.ray_x = game->math.horizontal_x;
			game->math.ray_y = game->math.horizontal_y;
			game->math.disT = game->math.disH;
		}
		if (game->math.ray_y == game->math.vertical_y)
			game->math.were_f = (game->p_y + sin(game->math.ray_angle) * (game->math.disT/64)) - (int)(game->p_y + sin(game->math.ray_angle) * (game->math.disT/64));
		else
			game->math.were_f = (game->p_x + cos(game->math.ray_angle) * (game->math.disT/64)) - (int)(game->p_x + cos(game->math.ray_angle) * (game->math.disT/64));
		game->math.weren = (int)(game->math.were_f * game->north.width);
		game->math.weree = (int)(game->math.were_f * game->east.width);
		game->math.werew = (int)(game->math.were_f * game->west.width);
		game->math.weres = (int)(game->math.were_f * game->south.width);

		game->math.correction_angle = game->p_a - game->math.ray_angle;
		if (game->math.correction_angle < 0)
			game->math.correction_angle += 2 * PI;
		if (game->math.correction_angle > 2 * PI)
			game->math.correction_angle-= 2 * PI;
		game->math.disT = game->math.disT * cos(game->math.correction_angle);
		game->math.lineH = (game->map.unit * SCREEN_LENGTH) / game->math.disT;
		game->math.lineO = (SCREEN_LENGTH / 2) - game->math.lineH / 2;
		while (game->math.lineH - SCREEN_LENGTH  + (gray * 2) < 0)
		{
			game->screen[gray][pixel_count] = 9211530;
			gray++;
		}
		while (z < game->math.lineH)
		{
			if (z + (int)game->math.lineO < 0 || z + (int)game->math.lineO > SCREEN_LENGTH - 1)
				z = z;
			else if ((game->math.werew + game->west.width - (game->math.werew*2) - 1) >= 0 && (game->math.werew + game->west.width - (game->math.werew*2) - 1) <=  game->west.width - 1 && ((z * game->west.width)/(int)game->math.lineH) <= game->west.width - 1 && ((z * game->west.width)/(int)game->math.lineH) >=0 && (game->math.ray_y == game->math.vertical_y) && (game->math.ray_angle >= P2 && game->math.ray_angle <= P3))
				game->screen[z + (int)game->math.lineO][pixel_count] = game->west.xpm[((z * game->west.width)/(int)game->math.lineH)][game->math.werew + game->west.width - (game->math.werew*2) - 1];
			else if ((game->math.weree) >= 0 && (game->math.weree <=  game->east.width - 1) && ((z * game->east.width)/(int)game->math.lineH) <= game->east.width - 1 && ((z * game->east.width)/(int)game->math.lineH) >=0 && (game->math.ray_y == game->math.vertical_y) && (game->math.ray_angle < P2 || game->math.ray_angle > P3))
				game->screen[z + (int)game->math.lineO][pixel_count] = game->east.xpm[((z * game->east.width)/(int)game->math.lineH)][game->math.weree];
			else if ((game->math.weres + game->south.width - (game->math.weres*2) - 1) >= 0 && (game->math.weres + game->south.width - (game->math.weres*2) - 1) <=  game->south.width - 1 && ((z * game->south.width)/(int)game->math.lineH) <= game->south.width - 1 && ((z * game->south.width)/(int)game->math.lineH) >=0 && (game->math.ray_y == game->math.horizontal_y) && (game->math.ray_angle < PI))
				game->screen[z + (int)game->math.lineO][pixel_count] = game->south.xpm[((z * game->south.width)/(int)game->math.lineH)][game->math.weres + game->south.width - (game->math.weres*2) - 1];
			else if ((game->math.weren) >= 0 && (game->math.weren <=  game->north.width - 1) && ((z * game->north.width)/(int)game->math.lineH) <= game->north.width - 1 && ((z * game->north.width)/(int)game->math.lineH) >=0 && (game->math.ray_y == game->math.horizontal_y) && (game->math.ray_angle >= PI))
				game->screen[z + (int)game->math.lineO][pixel_count] = game->north.xpm[((z * game->north.width)/(int)game->math.lineH)][game->math.weren];
			z++;
			gray++;
		}
		gray-=2;
		while (gray < 720)
		{
			game->screen[gray][pixel_count] = 9211530;
			gray++;
		}
		gray = 0;
		pixel_count++;
		z = 0; 		
		game->math.ray_angle += DR / (SCREEN_WIDTH / 66);
		if (game->math.ray_angle < 0)
			game->math.ray_angle += 2 * PI;
		if(game->math.ray_angle > 2 * PI)
			game->math.ray_angle -= 2 * PI;
	}
}

void	tab_to_image(t_game *game, t_data *img)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < SCREEN_LENGTH)
	{
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(img, x, y, game->screen[y][x]);
			x++;
		}
		y++;
		x = 0;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	screen_alloc(t_game *game)
{
	int y;

	y = 0;
	game->screen = (int **)malloc(sizeof(int *) * SCREEN_LENGTH + 1);
	while (y < SCREEN_LENGTH)
	{
		game->screen[y] = (int *)malloc(sizeof(int) * SCREEN_WIDTH + 1);
		y++;
	}
}

void	game_start(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx,SCREEN_WIDTH, SCREEN_LENGTH);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
	game->map.img.img = mlx_new_image(game->map.mlx, game->map.width * 16, game->map.width * 16);
	game->map.img.addr = mlx_get_data_addr(game->map.img.img, &game->map.img.bits_per_pixel, &game->map.img.line_length, &game->map.img.endian);
	gray_screen(&game->map.img, game->map.width * 16, game->map.length * 16);
	put_map(game, &game->map.img);
	put_player(game, &game->map.img);
	do_ray(game, &game->img);
	tab_to_image(game, &game->img);
	//mlx_mouse_hide(game->mlx, game->win);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_hook(game->win, 2, 1L << 0, code_moove, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_moove, game);
}

void	graphic_management(t_game *game)
{
	screen_alloc(game);
	game->mlx = mlx_init();
	game->map.mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_LENGTH, "cub3d");
	game->map.win = mlx_new_window(game->map.mlx, game->map.width * 16, game->map.length * 16, "minimap");
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
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,1,
		1,0,2,0,0,0,0,0,1,0,1,0,0,1,0,1,
		1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
		1,0,1,0,0,0,0,0,7,0,1,0,0,1,0,1,
		1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,
		1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	game.map.map = map;
	game.map.width = 16;
	game.map.length = 16;
	game.map.unit = 64;
	graphic_management(&game);
}
