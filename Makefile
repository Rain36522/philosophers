# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pudry <pudry@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 09:01:54 by pudry             #+#    #+#              #
#    Updated: 2024/09/11 14:43:36 by pudry            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET = \\033[0m
BLUE = \\033[1;34m
WHITE = \\033[0;37m
YELLOW = \\033[0;33m
RED = \\033[1;31m
GREEN = \\033[1;32m
BRWN = \\033[0; 33m

NAME = philosophers
CC = gcc
FLAGS = -Wall -Wextra -Werror
INCLUDES = includes/



SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=objet/%.o)


all: $(NAME)
	@echo "${GREEN}Philosophers compilation success${RESET}"

$(NAME): $(SRC) $(OBJ)
	@$(CC) $(OBJ) $(FLAGS) $(LIBFT_FILE) -o $(NAME)

clean:
	@rm -rf objet/

fclean: clean
	@rm -f $(NAME)

re: fclean all

objet/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDES)



.PHONY : fclean re all clean