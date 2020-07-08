# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssfar <ssfar@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 12:15:55 by ssfar             #+#    #+#              #
#    Updated: 2020/07/04 21:37:37 by ssfar            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = lem-in
LFT = libft/libft.a
VISU = visualiser/visu

CC = gcc
CFLAGS = -Wall -Wextra -Werror

INC_DIR = includes
SRC_DIR = sources
OBJ_DIR = objects

SRC_NAME =	algo.c \
			ant_display.c \
			bfs.c \
			clear.c \
			free_stuff.c \
			get_ant.c \
			info.c \
			init.c \
			is_room_link.c \
			les_mines.c \
			link_stuff.c \
			path.c \
			queue.c \
			read.c \
			reset_return.c \
			room_stuff.c \
			write_room.c \

SRC = $(addprefix $(SRC_DIR)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))

EOC			= \033[0;0m
RED			= \033[0;31m
GREEN		= \033[0;32m

all: $(LFT) $(NAME) $(VISU)

$(NAME): $(LFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $@
	@chmod 755 $(NAME)
	@printf "$(GREEN)$(NAME) Makefile : $(OBJ_DIR) and $(NAME) created\n$(EOC)"

$(LFT): FORCE
	@make -C ./libft
$(VISU): FORCE
	@make -C ./visualiser

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I libft/includes -c $< -o $@

clean:
	@make -C ./libft fclean
	@make -C ./visualiser fclean
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)$(NAME) Makefile : $(OBJ_DIR) deleted\n$(EOC)"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)$(NAME) Makefile : $(NAME) deleted\n$(EOC)"
re: fclean all
FORCE:
