LIBFT_PATH = ./libft
LIBFT      = $(LIBFT_PATH)/libft.a


SRCS = main.c

OBJS = ${SRCS:.c=.o}


NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
INCLUDES = -Iincludes

all : ${NAME}


${NAME} : ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

$(LIBFT):
	${MAKE} -C $(LIBFT_PATH) all

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
	
clean:
	@${MAKE} clean --silent -C ${LIBFT_PATH}
	@${RM} ${OBJS}
	@printf "MAKEFILE CLEAN\n"

fclean: clean
	@${MAKE} fclean --silent -C ${LIBFT_PATH}
	@${RM} ${NAME} ${BONUS}
	@printf "MAKEFILE FCLEAN\n"

re: fclean all

.PHONY: all clean fclean re