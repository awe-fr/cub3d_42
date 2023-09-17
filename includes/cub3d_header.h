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
	char **colors;
	int **xpm;
	int width;
	int length;
	int colors_number;
	int charactere_per_color;
}		t_xpm;

typedef	struct s_tmp {
	t_xpm	north;
	t_xpm	south;
	t_xpm	east;
	t_xpm	west;
	int northtxt;
	int southtxt;
	int easttxt;
	int westtxt;
	char **north_xpm;
	char **south_xpm;
	char **east_xpm;
	char **west_xpm;
}		t_tmp;

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
	t_xpm north;
	t_xpm south;
	t_xpm east;
	t_xpm west;
	t_map map;
	t_data img;
}		t_game;

int	esc_exit(int keycode, t_game *game);
int	cross_exit(t_game *game);
void	free_graphics(t_game *game);
void	free_tab(char **tab);
void	free_xpm(int **tab, int x);
void	free_tmp_value(t_tmp *tmp);
size_t	ft_strlen(char *str);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*word_dup(char *str, int start, int finish);
char	**st_split(char *s, char c);
char	**ft_split(char *s, char c);
char	**ft_image_to_char(int map);
char	*get_flat(int map);
void	xpm_to_char(char **xpm_char, t_xpm *xpm);
void	place_colors(char **xpm_info, t_xpm *xpm);
void	atoi_for_xpm(char *str, t_xpm *xpm);
void	init_assign(t_game *game);
void my_mlx_pixel_put(t_data *data, int x, int y, int colors);
float	dist(float ax, float ay, float bx, float by);
void	gray_screen(t_data *img, int width, int length);
void	aff_screen(t_game *game, t_data *img, int code, int size);
void	go_wall(int x, int y, t_data *img,int code);
void	look_left(t_game *game, t_data *img);
void	look_right(t_game *game, t_data *img);
void	open_east(t_game *game, t_data *img, t_data *img_map);
void	open_west(t_game *game, t_data *img, t_data *img_map);
void	open_north(t_game *game, t_data *img, t_data *img_map);
void	open_south(t_game *game, t_data *img, t_data *img_map);
void	go_up(t_game *game, t_data *img, t_data *img_map);
void	go_right(t_game *game, t_data *img, t_data *img_map);
void	go_left(t_game *game, t_data *img, t_data *img_map);
void	go_down(t_game *game, t_data *img, t_data *img_map);
void	put_map(t_game *game, t_data *img);
void	put_player(t_game *game, t_data *img);
void	orientation(t_game *game, t_data *img, t_data *img_map);
int	mouse_moove(int mouse_x, int mouse_y, void *gm);
int	code_moove(int keycode, void *gm);
void	go_player(t_game *game, int x, int y, t_data *img);
void	do_ray(t_game *game, t_data *img);
void	game_start(t_game *game);
void	graphic_management(t_game *game);
int	get_color(t_xpm *xpm, char **xpm_char, int x, int y);
int atoi_hexa(char *str);
void	check_color(t_tmp *tmp);
void	check_square(t_tmp *tmp);

#endif
