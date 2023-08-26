#ifndef CUB3D_HEADER_H
# define CUB3D_HEADER_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"

#define ESCAPE 65307

typedef struct s_game
{
	void	*mlx;
	void	*win;

}		t_game;

int	esc_exit(int keycode, t_game *game);
int	cross_exit(t_game *game);
void	free_graphics(t_game *game);

#endif
