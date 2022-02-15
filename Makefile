NAME		= cube

SRCFILE		= ./srcs/

HEADERSFILE	= ./headers/

CC			= clang

RM			= rm -f

FLAGS		= -Wall -Werror -Wextra -I/usr/include -Iheaders -Imlx_linux -O3 -c

FLAGSSUP	= -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

SRCFILE		=	./srcs/

SRCS		=	${SRCFILE}main.c\
				${SRCFILE}texture_checker.c\
				${SRCFILE}map_checker.c\
				${SRCFILE}free_stuff.c\
				${SRCFILE}global.c\
				${SRCFILE}parse.c\
				${SRCFILE}reader.c\
				${SRCFILE}utils.c\

OBJ		= 		${SRCS:.c=.o}

all: prog bonus

${NAME}: ${OBJ}
	${CC} -g ${OBJ} $(FLAGSSUP) -o $@

%.o : %.c
	${CC} ${FLAGS} -I ${HEADERSFILE} $< -o $@

prog: ${NAME}

clean:
	${RM} ${OBJ}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

rebonus: fclean bonus

.PHONY:	all clean fclean re rebonus prog bonus
