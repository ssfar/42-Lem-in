# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrobin <vrobin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 12:15:55 by ssfar             #+#    #+#              #
#    Updated: 2019/11/26 18:03:31 by vrobin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = lem-in

CC = gcc
CFLAGS = -Ofast -Wall -Wextra -Werror -I $(INC_DIR) -I ./libft/includes

INC_DIR = includes
SRC_DIR = sources
OBJ_DIR = objects

SRC_NAME =	V3_lem_in.c \
			room.c \
			link.c \
			hash.c \
			info.c \
			map.c \
			print.c \
			write_room_link.c \
			clear_unlinked.c \
			algo.c \
			update_link.c \

SRC = $(addprefix $(SRC_DIR)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))

EOC			= \033[0;0m
RED			= \033[0;31m
GREEN		= \033[0;32m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	@$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $@
	@chmod 755 $(NAME)
	@printf "$(GREEN)$(NAME) Makefile : $(OBJ_DIR) and $(NAME) created\n$(EOC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C ./libft fclean
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)$(NAME) Makefile : $(OBJ_DIR) deleted\n$(EOC)"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)$(NAME) Makefile : $(NAME) deleted\n$(EOC)"

re: fclean all
