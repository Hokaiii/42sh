##
## EPITECH PROJECT, 2025
## Title
## File description:
## Makefile
##

GREEN=\033[0;32m
BLUE=\033[0;34m
YELLOW=\033[0;33m
RED=\033[0;31m
RESET=\033[0m

NAME = 42sh

CC = gcc

CFLAGS = -lncurses -std=gnu99

SRC	=	$(wildcard src/*.c) \
	$(wildcard src/builtins/*.c) \
	$(wildcard src/builtins/alias/*.c) \
	$(wildcard src/core/*.c) \
	$(wildcard src/executor/*.c) \
	$(wildcard src/parser/*.c) \
	$(wildcard src/ncurses/code/*.c) \
	$(wildcard lib/*.c)

OBJ	=	$(SRC:.c=.o)

all: $(NAME)
	@echo "$(GREEN)Compilation Successful !$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compilation of $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)
	@echo "$(BLUE)Exec created: $(NAME)$(RESET)"

clean:
	@echo "$(RED)Delete files...$(RESET)"
	rm -f $(OBJ)
	rm -f 42sh
	find . -name "*.o" -type f -delete
	rm -f *.gcno *.gcda a.out

fclean: clean
	@echo "$(RED)Cleaning complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
