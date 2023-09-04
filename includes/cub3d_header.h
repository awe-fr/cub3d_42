#ifndef CUB3D_HEADER_H
# define CUB3D_HEADER_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "minilibx-linux/mlx.h"

#define ESCAPE 65307

#define SCREEN_WIDTH 1280
#define SCREEN_LENGTH 720
#define BACKGROUND 0x8c8e8a
#define PLAYER 0x0f056b
#define WALL 0xffffff

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533

#define MOUSE_x SCREEN_WIDTH / 2
#define MOUSE_y SCREEN_LENGTH / 2

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct s_map {
	void	*mlx;
	void	*win;
	int *map;
	int width;
	int length;
	int unit;
	t_data img;
}		t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int spawn_x;
	int spawn_y;
	float p_x;
	float p_y;
	float p_dx;
	float p_dy;
	float p_a;
	t_map map;
	t_data img;
}		t_game;

int	esc_exit(int keycode, t_game *game);
int	cross_exit(t_game *game);
void	free_graphics(t_game *game);

#endif
