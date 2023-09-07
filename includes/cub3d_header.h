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
#define DOOR_OPEN 0x80e56a
#define DOOR_CLOSE 0xdc1b1c

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533

#define MOUSE_X SCREEN_WIDTH / 2
#define MOUSE_Y SCREEN_LENGTH / 2

typedef struct s_xpm {
	char **xpm;
	char **colors;
	int width;
	int length;
	int number_of_color;
	int charactere_per_color;
}		t_xpm;

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
	float next_wall;
	t_xpm wall;
	t_xpm door;
	t_map map;
	t_data img;
}		t_game;

int	esc_exit(int keycode, t_game *game);
int	cross_exit(t_game *game);
void	free_graphics(t_game *game);
size_t	ft_strlen(char *str);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_image_to_char(int map);
char	*get_flat(int map);

#endif
