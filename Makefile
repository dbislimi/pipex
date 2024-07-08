LIBFT_PATH = ./libft
LIBFT      = $(LIBFT_PATH)/libft.a

PIPEX_PATH = ./srcs/pipex
BONUS_PATH = ./srcs/bonus

SRCS = ${addprefix ${PIPEX_PATH}/, pipex.c \
									pipex_utils.c \
									execution.c}
SRCS_B = ${addprefix ${BONUS_PATH}/,pipex_bonus.c \
									execution_bonus.c \
									pipex_utils_bonus.c \
									here_doc.c}
OBJS = ${SRCS:.c=.o}
OBJS_B = ${SRCS_B:.c=.o}

NAME = pipex
BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
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