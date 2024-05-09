NAME = minitalk
NAME_SERVER = server
NAME_CLIENT = client

CC = cc
HEADER = ./libft
CFLAGS = -Wextra -Werror -Wall -g -I$(HEADER)
COMPILE = $(CC) $(CFLAGS) -c
ARCHIVE = ar rc $(NAME)

LIBFT_DIR = ./libft

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
YELLOW=\033[0;33m
RESET=\033[0m

SRC_CLIENT =	./src/client.c 

SRC_SERVER =	./src/server.c 


all: $(NAME)

$(NAME): $(SRC_SERVER) $(SRC_CLIENT)
	make all -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -I. -I$(HEADER) $(SRC_SERVER) -L$(LIBFT_DIR) -lft -o $(NAME_SERVER)
	$(CC) $(CFLAGS) -I. -I$(HEADER) $(SRC_CLIENT) -L$(LIBFT_DIR) -lft -o $(NAME_CLIENT)
	@echo "$(YELLOW)	MINITALK COMPILED! 📲✅$(RESET)"
	@echo "$(YELLOW)	Run ./client or ./server$(RESET)"

bonus: $(NAME)

RM = rm -f

clean:
	make clean -C $(LIBFT_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)
	@echo "$(RED)	MINITALK DESTROYED 📵 $(RESET)"

re: fclean all

.PHONY: all clean fclean re
.SILENT: