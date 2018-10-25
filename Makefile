# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmalfroy <cmalfroy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by cmalfroy          #+#    #+#              #
#    Updated: 2018/02/20 12:04:56 by cmalfroy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = ft_ssl

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

LIB = libft

LDFLAGS = -Llibft

LDLIBS = -lft

SRC_PATH = src

SRC_NAME = \
	md5.c ft_ssl.c sha256.c hash.c

AR = ar rc

INC_LIB = -I libft/include

CPPFLAGS = -I include

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)


SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME) $(NAME2)

$(NAME): $(OBJ)
	@make -C $(LIB)
	@echo $(NAME) ": Sources compiling..."
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "Executable "$(NAME)" made"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(INC_LIB) -o $@ -c $<

clean:
	@make fclean -C $(LIB)
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH) || true
	@rm -rf $(OBJ_PATH2) || true
	@echo $(OBJ_PATH)" supprimé !"

fclean: clean
	@rm -f $(NAME)
	@echo "Executable de "$(NAME)" supprimé !"

re: fclean all
	@echo "Make re done !"

norme:
	norminette $(SRC)
	norminette $(INC_PATH)