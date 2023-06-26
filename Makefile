DARKGRAY=\033[1;30m
RED=\033[0;31m
LIGHTRED=\033[1;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
LIGHTPURPLE=\033[1;35m
CYAN=\033[0;36m
WHITE=\033[1;37m
SET=\033[0m

SRC		= main.c get_data.c signals.c utils.c pipesplit.c get_redirsep.c take_args.c get_path.c utils2.c utils3.c get_line.c utils4.c run.c fd.c builtins.c special.c redirection.c heredoc.c utils5.c utils6.c utils7.c list_export.c utils8.c utils9.c utils10.c

NAME	= minishell
LIB		= ./lib/.minishell
OS		= $(shell uname -s)

ifeq ($(OS), Linux)
		CFLAGS = -g -lreadline ./libft/libft.a
else
		CFLAGS = -g -Wall -Wextra -Werror ./libft/libft.a -lreadline -I./lib/readline/include -L./lib/readline/lib
endif

all: $(LIB) $(NAME)

$(LIB):
	@make -C ./lib

$(NAME) : $(SRC)
	@make -sC ./libft
	@echo "$(YELLOW)Libft Compiled$(SET)"
	@gcc $(SRC) $(CFLAGS) -o $(NAME)
	@echo "$(CYAN)minishell Compiled$(SET)"

clean:
	@make fclean -sC ./libft
	@rm -rf minishell
	@echo "Cleaned"

fclean: clean
	make fclean -C ./lib
re: clean all

.PHONY: re clean fclean all

