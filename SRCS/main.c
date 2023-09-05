#include "../includes/cub3d_header.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

float	dist(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt(((bx-ax) * (bx-ax)) + ((by-ay) * (by-ay))));
}

void	gray_screen(t_data *img, int width, int length)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x <= width)
	{
		while(y <= length)
		{
			my_mlx_pixel_put(img, x, y, BACKGROUND);
			y++;
		}
		x++;
		y = 0;
	}
}

void	aff_screen(t_game *game, t_data *img, int code, int size)
{
	int count_x;
	int count_y;

	count_y = 0;
	count_x = 0;
	while(count_y != size)
	{
		while(count_x != size)
		{
			my_mlx_pixel_put(img, (game->p_x * 16) + count_x, (game->p_y * 16) + count_y, code);
			count_x++;
		}
		count_y++;
		count_x = 0;
	}
}

void	go_wall(int x, int y, t_data *img,int code)
{
	int count_x;
	int count_y;

	count_y = 0;
	count_x = 0;
	while(count_y != 16)
	{
		while(count_x != 16)
		{
			my_mlx_pixel_put(img, (x * 16) + count_x, (y * 16) + count_y, code);
			count_x++;
		}
		count_y++;
		count_x = 0;
	}
}
/*
void	do_line(t_game *game, t_data *img, int code)
{
	int count_x;
	int count_y;

	count_y = 0;
	count_x = 0;
	while(count_y != 1)
	{
		while(count_x != 20)
		{
			aff_screen(game, img, PLAYER, 5);
			my_mlx_pixel_put(img, (((game->p_x + 0.04) * game->map.unit)) + (game->p_dx / 5) * count_x, (((game->p_y + 0.04) * game->map.unit)) + (game->p_dy / 5) * count_x, code);
			count_x++;
		}
		count_y++;
		count_x = 0;
	}
}*/

void	go_player(t_game *game, int x, int y, t_data *img)
{
	game->p_x = (float)x + 0.45;
	game->p_y = (float)y + 0.45;
	game->p_a = PI/2;
	game->p_dx = cos(game->p_a) * 5;
	game->p_dy = sin(game->p_a) * 5;
	aff_screen(game, img, PLAYER, 2);
}

void	put_map(t_game *game, t_data *img)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(y < game->map.length)
	{
		while(x < game->map.width)
		{
			if (game->map.map[x + y * game->map.width] == 1)
				go_wall(x, y, img, WALL);
			else if (game->map.map[x + y * game->map.width] == 7)
				go_wall(x, y, img, DOOR_CLOSE);
			else if (game->map.map[x + y * game->map.width] == 6)
				go_wall(x, y, img, DOOR_OPEN);
			x++;
		}
		y++;
		x = 0;
	}
}

void	put_player(t_game *game, t_data *img)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(y < game->map.length)
	{
		while(x < game->map.width)
		{
			if (game->map.map[x + y * game->map.width] == 2)
			 	go_player(game, x, y, img);
			x++;
		}
		y++;
		x = 0;
	}
}

void	do_ray(t_game *game, t_data *img)
{
	int r,mx,my,mp,dof; float rx,ry,ra,xo,yo,disT;
	ra = game->p_a - DR * 30;
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
				disH = dist(game->p_x * 64, game->p_y * 64, hx, hy, ra);
				dof = 8;
			}
			else if ((game->map.map[(int)(game->p_x + game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy / game->map.unit) * game->map.width] != 1) && (game->map.map[(int)(game->p_x + game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy / game->map.unit) * game->map.width] != 7))
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
				disV = dist(game->p_x * 64, game->p_y * 64, vx, vy, ra);
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
		ca = game->p_a - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca-= 2 * PI;
		disT = disT * cos(ca);
		if (r == SCREEN_WIDTH / 2)
		{
			game->next_wall = disT / 64;
			//printf("%f, %f, %f\n", disT / 64, cos(ca), game->p_a / PI);
		}
		lineH = (game->map.unit * SCREEN_LENGTH) / disT;
		if (lineH > SCREEN_LENGTH)
			lineH = SCREEN_LENGTH;
		lineO = (SCREEN_LENGTH / 2) - lineH / 2;
		while (z < lineH)
		{
			my_mlx_pixel_put(img, pixel_count, z + lineO, 0xFF0000);
			z++;
		}
		pixel_count++;
		z = 0; 		
		ra += DR / (SCREEN_WIDTH / 60);
		if (ra < 0)
			ra += 2 * PI;
		if(ra > 2 * PI)
			ra -= 2 * PI;
	}
}

void	go_up(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	aff_screen(game, img_map, BACKGROUND, 2);
	put_map(game, img_map);
	if ((game->map.map[(int)(game->p_x + game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy / game->map.unit) * game->map.width] != 1) && (game->map.map[(int)(game->p_x + game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy / game->map.unit) * game->map.width] != 7))
	{	
		game->p_x += game->p_dx / game->map.unit;
		game->p_y += game->p_dy / game->map.unit;
	}
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	go_right(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	aff_screen(game, img_map, BACKGROUND, 2);
	put_map(game, img_map);
	if ((game->map.map[(int)(game->p_x - game->p_dy / game->map.unit) + (int)(game->p_y + game->p_dx / game->map.unit) * game->map.width] != 1) && (game->map.map[(int)(game->p_x - game->p_dy / game->map.unit) + (int)(game->p_y + game->p_dx / game->map.unit) * game->map.width] != 7))
	{	
		game->p_x -= game->p_dy / game->map.unit;
		game->p_y += game->p_dx / game->map.unit;
	}
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	go_left(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	aff_screen(game, img_map, BACKGROUND, 2);
	put_map(game, img_map);
	if ((game->map.map[(int)(game->p_x + game->p_dy / game->map.unit) + (int)(game->p_y - game->p_dx / game->map.unit) * game->map.width] != 1) && (game->map.map[(int)(game->p_x + game->p_dy / game->map.unit) + (int)(game->p_y - game->p_dx / game->map.unit) * game->map.width] != 7))
	{	
		game->p_x += game->p_dy / game->map.unit;
		game->p_y -= game->p_dx / game->map.unit;
	}
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	go_down(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	aff_screen(game, img_map, BACKGROUND, 2);
	put_map(game, img_map);
	if ((game->map.map[(int)(game->p_x - game->p_dx / game->map.unit) + (int)(game->p_y - game->p_dy / game->map.unit) * game->map.width] != 1) && (game->map.map[(int)(game->p_x - game->p_dx / game->map.unit) + (int)(game->p_y - game->p_dy / game->map.unit) * game->map.width] != 7))
	{	
		game->p_x -= game->p_dx / game->map.unit;
		game->p_y -= game->p_dy / game->map.unit;
	}
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	look_left(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	game->p_a -= 0.05;
	if (game->p_a < 0)
		game->p_a += 2 * PI;
	game->p_dx = cos(game->p_a) * 5;
	game->p_dy = sin(game->p_a) * 5;
	do_ray(game, img);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	look_right(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	game->p_a += 0.05;
	if (game->p_a > 2 * PI)
		game->p_a -= 2 * PI;
	game->p_dx = cos(game->p_a) * 5;
	game->p_dy = sin(game->p_a) * 5;
	do_ray(game, img);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	open_south(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	gray_screen(&game->map.img, game->map.width * 16, game->map.length * 16);
	aff_screen(game, img_map, BACKGROUND, 2);
	if (game->map.map[(int)game->p_x + ((int)(game->p_y + 1) * game->map.width)] == 7)
		game->map.map[(int)game->p_x + ((int)(game->p_y + 1) * game->map.width)] = 6;
	else if (game->map.map[(int)game->p_x + ((int)(game->p_y + 1) * game->map.width)] == 6)
		game->map.map[(int)game->p_x + ((int)(game->p_y + 1) * game->map.width)] = 7;
	put_map(game, img_map);
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	open_north(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	gray_screen(&game->map.img, game->map.width * 16, game->map.length * 16);
	aff_screen(game, img_map, BACKGROUND, 2);
	if (game->map.map[(int)game->p_x + ((int)(game->p_y - 1) * game->map.width)] == 7)
		game->map.map[(int)game->p_x + ((int)(game->p_y - 1) * game->map.width)] = 6;
	else if (game->map.map[(int)game->p_x + ((int)(game->p_y - 1) * game->map.width)] == 6)
		game->map.map[(int)game->p_x + ((int)(game->p_y - 1) * game->map.width)] = 7;
	put_map(game, img_map);
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	open_west(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	gray_screen(&game->map.img, game->map.width * 16, game->map.length * 16);
	aff_screen(game, img_map, BACKGROUND, 2);
	if (game->map.map[(int)(game->p_x - 1) + ((int)game->p_y * game->map.width)] == 7)
		game->map.map[(int)(game->p_x - 1) + ((int)game->p_y * game->map.width)] = 6;
	else if (game->map.map[(int)(game->p_x - 1) + ((int)game->p_y * game->map.width)] == 6)
		game->map.map[(int)(game->p_x - 1) + ((int)game->p_y * game->map.width)] = 7;
	put_map(game, img_map);
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	open_east(t_game *game, t_data *img, t_data *img_map)
{
	gray_screen(&game->img, SCREEN_WIDTH, SCREEN_LENGTH);
	gray_screen(&game->map.img, game->map.width * 16, game->map.length * 16);
	aff_screen(game, img_map, BACKGROUND, 2);
	if (game->map.map[(int)(game->p_x + 1) + ((int)game->p_y * game->map.width)] == 7)
		game->map.map[(int)(game->p_x + 1) + ((int)game->p_y * game->map.width)] = 6;
	else if (game->map.map[(int)(game->p_x + 1) + ((int)game->p_y * game->map.width)] == 6)
		game->map.map[(int)(game->p_x + 1) + ((int)game->p_y * game->map.width)] = 7;
	put_map(game, img_map);
	aff_screen(game, img_map, PLAYER, 2);
	do_ray(game, img);
	mlx_put_image_to_window(game->map.mlx, game->map.win, game->map.img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	orientation(t_game *game, t_data *img, t_data *img_map)
{
	if (game->p_a / PI > 0.25 && game->p_a / PI < 0.75)
		open_south(game, img, img_map);
	else if (game->p_a / PI > 1.25 && game->p_a / PI < 1.75)
		open_north(game, img, img_map);
	else if (game->p_a / PI > 0.75 && game->p_a / PI < 1.25)
		open_west(game, img, img_map);
	else if ((game->p_a / PI > 1.75 && game->p_a / PI <= 1.999999999) || (game->p_a / PI >= 0 && game->p_a / PI < 0.25))
		open_east(game, img, img_map);
}

int	code_moove(int keycode, void *gm)
{
	t_game *game;

	game = (t_game *)gm;
	if (keycode == 119)
		go_up(game, &game->img, &game->map.img);
	else if (keycode == 115)
		go_down(game, &game->img, &game->map.img);
	else if (keycode == 100)
		go_right(game, &game->img, &game->map.img);
	else if (keycode == 97)
		go_left(game, &game->img, &game->map.img);
	else if (keycode == 101)
		orientation(game, &game->img, &game->map.img);
	else if (keycode == 65363)
		look_right(game, &game->img, &game->map.img);
	else if (keycode == 65361)
		look_left(game, &game->img, &game->map.img);
	else if (keycode == ESCAPE)
		esc_exit(keycode, game);
}

int	mouse_moove(int mouse_x, int mouse_y, void *gm)
{
	t_game *game;

	game = (t_game *)gm;
	if (mouse_y >= MOUSE_Y + 100)
		mlx_mouse_move(game->mlx, game->win, MOUSE_X, MOUSE_Y);
	else if (mouse_x >= MOUSE_X + 100)
	{
		mlx_mouse_move(game->mlx, game->win, MOUSE_X, MOUSE_Y);
		look_right(game, &game->img, &game->map.img);
	}
	else if (mouse_x <= MOUSE_X -100)
	{
		mlx_mouse_move(game->mlx, game->win, MOUSE_X, MOUSE_Y);	
		look_left(game, &game->img, &game->map.img);
	}
	else if (mouse_y <= MOUSE_Y - 100)
		mlx_mouse_move(game->mlx, game->win, MOUSE_X, MOUSE_Y);
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
