#include "../includes/cub3d_header.h"

void	do_ray(t_game *game, t_data *img)
{
	game->math.ray_angle = game->p_a - DR * 33;
	if (game->math.ray_angle < 0)
		game->math.ray_angle += 2 * PI;
	if(game->math.ray_angle > 2 * PI)
		game->math.ray_angle -= 2 * PI;
	game->math.ray = 0;
	int pixel_count = 0;
	while (game->math.ray<SCREEN_WIDTH)
	{
		ray_x(game);
		ray_y(game);
		game->math.ray++;
		if(game->math.dis_v < game->math.dis_h)
		{
			game->math.ray_x = game->math.vertical_x;
			game->math.ray_y = game->math.vertical_y;
			game->math.dis_t = game->math.dis_v;
		}
		if(game->math.dis_h < game->math.dis_v)
		{
			game->math.ray_x = game->math.horizontal_x;
			game->math.ray_y = game->math.horizontal_y;
			game->math.dis_t = game->math.dis_h;
		}
		if (game->math.ray_y == game->math.vertical_y)
			game->math.were_f = (game->p_y + sin(game->math.ray_angle) * (game->math.dis_t/64)) - (int)(game->p_y + sin(game->math.ray_angle) * (game->math.dis_t/64));
		else
			game->math.were_f = (game->p_x + cos(game->math.ray_angle) * (game->math.dis_t/64)) - (int)(game->p_x + cos(game->math.ray_angle) * (game->math.dis_t/64));
		game->math.weren = (int)(game->math.were_f * game->north.width);
		game->math.weree = (int)(game->math.were_f * game->east.width);
		game->math.werew = (int)(game->math.were_f * game->west.width);
		game->math.weres = (int)(game->math.were_f * game->south.width);
		game->math.correction_angle = game->p_a - game->math.ray_angle;
		if (game->math.correction_angle < 0)
			game->math.correction_angle += 2 * PI;
		if (game->math.correction_angle > 2 * PI)
			game->math.correction_angle-= 2 * PI;
		game->math.dis_t = game->math.dis_t * cos(game->math.correction_angle);
		game->math.lineh = (game->map.unit * SCREEN_LENGTH) / game->math.dis_t;
		game->math.lineo = (SCREEN_LENGTH / 2) - game->math.lineh / 2;
		pixel_count = print_line(game, pixel_count);
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
