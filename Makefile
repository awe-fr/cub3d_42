NAME = cub3d

SRCS = SRCS/*.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra
RM = rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(SRCS) includes/minilibx-linux/libmlx.a -lXext -lX11 -o $(NAME)
				
clean:
			$(RM) $(OBJS)
			
fclean:		clean
			$(RM) $(NAME)
			
re:			fclean all

.PHONY:		all clean fclean re
