LIBFT_PATH = ./libft
LIBFT      = $(LIBFT_PATH)/libft.a

PIPEX_PATH = ./srcs/pipex
BONUS_PATH = ./srcs/bonus

SRCS = ${addprefix ${PIPEX_PATH}/, pipex.c}
SRCS_B = ${addprefix ${BONUS_PATH}/,main.c move_utils.c parsing.c so_long_utils.c parsing_utils.c parsing_utils2.c flood_fill.c \
		free.c events.c load_textures.c manage_textures.c move.c sprite.c}
OBJS = ${SRCS:.c=.o}
OBJS_B = ${SRCS_B:.c=.o}

NAME = pipex
BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
INCLUDES = -Iincludes

all : ${NAME}

bonus : ${BONUS}

${NAME} : ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} 

${BONUS} : ${LIBFT} ${OBJS_B}
	${CC} ${CFLAGS} -o ${BONUS} ${OBJS_B} ${LIBFT}

$(LIBFT):
	${MAKE} -C $(LIBFT_PATH) all

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
	
clean:
	@${MAKE} clean --silent -C ${LIBFT_PATH}
	@${RM} ${OBJS} ${OBJS_B}
	@printf "MAKEFILE CLEAN\n"

fclean: clean
	@${MAKE} fclean --silent -C ${LIBFT_PATH}
	@${RM} ${NAME} ${BONUS}
	@printf "MAKEFILE FCLEAN\n"

re: fclean all

.PHONY: all clean fclean re