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

void	gray_screen(t_game *game, t_data *img)
{
	int x;
	int y;

	x = 1;
	y = 1;
	while (x <= SCREEN_WIDTH)
	{
		while(y <= SCREEN_LENGTH)
		{
			my_mlx_pixel_put(img, x, y, BACKGROUND);
			y++;
		}
		x++;
		y = 1;
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
			my_mlx_pixel_put(img, (game->p_x * game->map.unit) + count_x, (game->p_y * game->map.unit) + count_y, code);
			count_x++;
		}
		count_y++;
		count_x = 0;
	}
}

void	go_wall(t_game *game, int x, int y, t_data *img)
{
	int count_x;
	int count_y;

	count_y = 0;
	count_x = 0;
	while(count_y != game->map.unit)
	{
		while(count_x != game->map.unit)
		{
			my_mlx_pixel_put(img, (x * game->map.unit) + count_x, (y * game->map.unit) + count_y, WALL);
			count_x++;
		}
		count_y++;
		count_x = 0;
	}
}

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
}

void	go_player(t_game *game, int x, int y, t_data *img)
{
	game->p_x = (float)x + 0.50;
	game->p_y = (float)y + 0.50;
	game->p_a = PI/2;
	game->p_dx = cos(game->p_a) * 5;
	game->p_dy = sin(game->p_a) * 5;
	aff_screen(game, img, PLAYER, 5);
	do_line(game, img, PLAYER);
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
				go_wall(game, x, y, img);
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
	int i = 0;
	int z = 0;
	int pixel_count = 1;
	r = 0;
	while (r<60)
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
			if (mp > 0 && mp<game->map.width*game->map.length && game->map.map[mp] == 1) 
			{
				hx = rx;
				hy = ry;
				disH = dist(game->p_x * 64, game->p_y * 64, hx, hy, ra);
				dof = 8;
			}
			else
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
			if (mp > 0 && mp<game->map.width*game->map.length && game->map.map[mp] == 1)
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
		if (((rx < 0 || rx > game->map.width * game->map.unit) && (ry < 0 || ry > game->map.length * game->map.unit)))
			return ;
		my_mlx_pixel_put(img, rx, ry, 0xFF0000);
		my_mlx_pixel_put(img, rx+1, ry, 0xFF0000);
		my_mlx_pixel_put(img, rx+1, ry+1, 0xFF0000);
		my_mlx_pixel_put(img, rx, ry+1, 0xFF0000);
		ca = game->p_a - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca-= 2 * PI;
		disT = disT * cos(ca);
		lineH = (game->map.unit * 320) / disT;
		if (lineH > 320)
			lineH = 320;
		lineO = 160 - lineH / 2;
		while (i < 8)
		{
			while (z < lineH)
			{
				my_mlx_pixel_put(img, pixel_count + 520, z + lineO, 0xFF0000);
				z++;
			}
			pixel_count++;
			z = 0;
			i++;
		}
		i = 0; 		
		ra += DR;
		if (ra < 0)
			ra += 2 * PI;
		if(ra > 2 * PI)
			ra -= 2 * PI;
	}
}

void	go_up(t_game *game, t_data *img)
{
	gray_screen(game, img);
	do_line(game, img, BACKGROUND);
	aff_screen(game, img, BACKGROUND, 5);
	put_map(game, &game->img);
	if (game->map.map[(int)(game->p_x + game->p_dx / game->map.unit) + (int)(game->p_y + game->p_dy / game->map.unit) * game->map.width] != 1)
	{	
		game->p_x += game->p_dx / game->map.unit;
		game->p_y += game->p_dy / game->map.unit;
	}
	printf("%f, %f, %d\n", game->p_x, game->p_y, game->map.map[(int)game->p_x + (int)game->p_y * 8]);
	aff_screen(game, img, PLAYER, 5);
	do_line(game, img, PLAYER);
	do_ray(game, img);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	go_left(t_game *game, t_data *img)
{
	gray_screen(game, img);
	do_line(game, img, BACKGROUND);
	put_map(game, &game->img);
	game->p_a -= 0.1;
	if (game->p_a < 0)
		game->p_a += 2 * PI;
	game->p_dx = cos(game->p_a) * 5;
	game->p_dy = sin(game->p_a) * 5;
	do_line(game, img, PLAYER);
	do_ray(game, img);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	go_right(t_game *game, t_data *img)
{
	gray_screen(game, img);
	do_line(game, img, BACKGROUND);
	put_map(game, &game->img);
	game->p_a += 0.1;
	if (game->p_a > 2 * PI)
		game->p_a -= 2 * PI;
	game->p_dx = cos(game->p_a) * 5;
	game->p_dy = sin(game->p_a) * 5;
	do_line(game, img, PLAYER);
	do_ray(game, img);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	go_down(t_game *game,   t_data *img)
{
	gray_screen(game, img);
	do_line(game, img, BACKGROUND);
	aff_screen(game, img, BACKGROUND, 5);
	put_map(game, &game->img);
	if (game->map.map[(int)(game->p_x - game->p_dx / game->map.unit) + (int)(game->p_y - game->p_dy / game->map.unit) * game->map.width] != 1)
	{	
		game->p_x -= game->p_dx / game->map.unit;
		game->p_y -= game->p_dy / game->map.unit;
	}
	aff_screen(game, img, PLAYER, 5);
	do_line(game, img, PLAYER);
	do_ray(game, img);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int	code_moove(int keycode, void *gm)
{
	t_game *game;

	game = (t_game *)gm;
	if (keycode == 119)
		go_up(game, &game->img);
	else if (keycode == 100)
		go_right(game, &game->img);
	else if (keycode == 97)
		go_left(game, &game->img);
	else if (keycode == 115)
		go_down(game, &game->img);
	else if (keycode == ESCAPE)
		esc_exit(keycode, game);
}

void	game_start(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx,SCREEN_WIDTH, SCREEN_LENGTH);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
	gray_screen(game, &game->img);
	put_map(game, &game->img);
	put_player(game, &game->img);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_hook(game->win, 2, 1L << 0, code_moove, game);
}

void	graphic_management(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_LENGTH, "cub3d");
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
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,1,1,1,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
	};
	game.map.map = map;
	game.map.width = 8;
	game.map.length = 8;
	game.map.unit = 64;
	graphic_management(&game);
}
