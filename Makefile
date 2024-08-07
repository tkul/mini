NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=address -g
M_SRC = main.c signal.c start.c lexer.c dollar.c dollar_utils.c redirections.c remove.c utils.c
LIB_SRC = lib/ft_atoi.c lib/ft_bzero.c lib/ft_isalnum.c lib/ft_isalpha.c lib/ft_isascii.c lib/ft_isdigit.c lib/ft_isprint.c lib/ft_memchr.c lib/ft_memcmp.c lib/ft_memcpy.c lib/ft_memmove.c lib/ft_memset.c lib/ft_strchr.c lib/ft_strlcat.c lib/ft_strlcpy.c lib/ft_strlen.c lib/ft_strncmp.c lib/ft_strnstr.c lib/ft_strrchr.c lib/ft_tolower.c lib/ft_toupper.c lib/ft_calloc.c lib/ft_strdup.c lib/ft_putchar_fd.c lib/ft_putstr_fd.c lib/ft_putendl_fd.c lib/ft_putnbr_fd.c lib/ft_substr.c lib/ft_strjoin.c lib/ft_strtrim.c lib/ft_split.c lib/ft_itoa.c lib/ft_strmapi.c lib/ft_striteri.c
SRC = $(M_SRC) $(LIB_SRC)
OBJ = $(SRC:.c=.o)
READLINE = -L./lib/readline/lib -I./lib/readline/include/readline -lreadline -ltinfo
DIR     = $(shell echo $(PWD))
RM = rm -rf
RL = ./lib/readline/lib/libreadline.a

all: $(NAME)

$(NAME): $(RL) $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(READLINE)

$(RL):
		@echo "Downloading readline"
		@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2-rc1.tar.gz
		@tar -xvf readline-8.2-rc1.tar.gz
		@$(RM) readline-8.2-rc1.tar.gz
		@cd readline-8.2-rc1 && ./configure --prefix=$(DIR)/lib/readline && make && make install
		@$(RM) readline-8.2-rc1
		@ echo "Readline installed"

RLclean:
		@$(RM) lib/readline
		@echo "Readline removed"

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re push