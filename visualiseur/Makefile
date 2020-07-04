# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/11 17:08:22 by ssfar             #+#    #+#              #
#    Updated: 2020/03/11 14:36:23 by vrobin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, install

NAME = visu

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR) -I ../libft/includes


INC_DIR = includes
SRC_DIR = sources
OBJ_DIR = objects


SRC_NAME = main.c init.c read.c display.c is.c free.c store.c other.c other2.c ant.c quit.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))

EOC			= \033[0;0m
RED			= \033[0;31m
GREEN		= \033[0;32m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ../libft
	@$(CC) $(CFLAGS) $(shell sdl2-config --libs) -lSDL2_ttf ../libft/libft.a $(OBJ) -o $@
	@chmod 755 $(NAME)
	@printf "$(GREEN)$(NAME) Makefile : $(OBJ_DIR) and $(NAME) created\n$(EOC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(shell sdl2-config --cflags) -c $< -o $@

clean:
	@make -C ../libft fclean
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)$(NAME) Makefile : $(OBJ_DIR) deleted\n$(EOC)"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)$(NAME) Makefile : $(NAME) deleted\n$(EOC)"

re: fclean all

install :
	@brew install sdl2
	@brew install sdl2_tff
