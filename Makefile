SRCS = main.c utils.c parsing/errors.c parsing/read.c parsing/parse_textures.c parsing/utils.c \
parsing/utils2.c parsing/parse_map.c parsing/parse_map2.c parsing/utils3.c parsing/debug.c \
parsing/validate.c parsing/parse_textures2.c \
engine/engine.c engine/errors.c engine/free.c engine/textures.c \
engine/raycast_walls.c engine/raycast_floor.c engine/keys.c engine/pos.c \
engine/exit.c

OBJS = $(addprefix cub/src/, ${SRCS:.c=.o})
DEPS = cub/includes/cub3d.h cub/includes/parsing.h cub/includes/keys.h

PLATFORM := $(shell uname)
RM = rm -f
CC = clang
ifeq ($(PLATFORM), Linux)
CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx -O3 -g
LINKER_FLAGS = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
endif
ifeq ($(PLATFORM), Darwin)
CFLAGS = -Wall -Wextra -Werror -Imlx -g
LINKER_FLAGS = -Lmlx -lmlx -L/usr/X11/include/../lib -lXext -lX11 -lm
endif

NAME = cub3D

.c.o:
	${CC} ${CFLAGS} -I./mlx -I./libft -I./cub/includes -c $< -o ${<:.c=.o}

all: 	${NAME}

${NAME}:	${OBJS} ${DEPS}
		$(MAKE) -C ./mlx
		$(MAKE) bonus -C ./libft
		${CC} -o ${NAME} ${OBJS} ${LINKER_FLAGS} ./libft/libft.a

clean:
		$(MAKE) clean -C ./mlx
		$(MAKE) clean -C ./libft
		${RM} ${OBJS}

fclean:	clean
		$(MAKE) clean -C ./mlx
		$(MAKE) fclean -C ./libft
		${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re
