NAME = minishell

PATH_BUILD	:= build

SRCS =	minishell.c \
		src/scanner.c \
		src/scanner1.c \
		src/cd.c \
		src/echo.c \
		src/env.c \
		src/exit.c \
		src/export.c \
		src/pwd.c \
		src/unset.c \
		src/pipes.c \
		src/execute.c \
		src/redirection.c \
		utils/utils1.c \
		utils/utils2.c \
		utils/utils3.c \
		src/parser.c \
		src/parser2.c \
		src/parser3.c \
		src/parser4.c \
		src/parse_errors.c \
		src/signals.c \

OBJS = ${SRCS:%.c=$(PATH_BUILD)/%.o}

CC		= gcc
RM		= rm -fr

#CFLAGS = -Wall -Wextra -Werror 
CFLAGS = -I ~/.brew/opt/readline/include -Wall -Wextra -Werror 
RL = -I ~/.brew/opt/readline/include -L ~/.brew/opt/readline/lib -lreadline

all:	${NAME}

.c.o:
# ${CC} ${CFLAGS} -c $< -o $@
		${CC} ${CFLAGS} -c $< -o $@ ${RL}

$(NAME): ${OBJS}
# $(CC) $(SRCS) -lreadline -o ${NAME}
		$(CC) $(SRCS) -o ${NAME} ${RL}

$(PATH_BUILD)/%.o:	%.c
		mkdir -p $(dir $@)
		$(CC) ${CFLAGS} -c $< -o $@

clean:
		${RM} ${PATH_BUILD}

fclean:	clean
		${RM} ${NAME} 

re:		fclean all