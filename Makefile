# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 11:51:31 by smoore            #+#    #+#              #
#    Updated: 2025/02/07 11:51:34 by smoore           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc -Wall -Wextra -Werror -g
LIBFT = libft/libft.a
HEADER = inc/data.h
IFLAG = -I./inc -I./libft/include
SRC = $(wildcard src/*.c)
#builtins  exec  main.c  parser  tokens  utils
SRC1 = $(wildcard src/utils/*.c)
SRC2 = $(wildcard src/builtins/*.c)
SRC3 = $(wildcard src/tokens/*.c)
SRC4 = $(wildcard src/parser/*.c)
SRC5 = $(wildcard src/exec/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC)) \
	$(patsubst src/utils/%.c, obj/%.o, $(SRC1))\
	$(patsubst src/builtins/%.c, obj/%.o, $(SRC2))\
	$(patsubst src/tokens/%.c, obj/%.o, $(SRC3))\
	$(patsubst src/parser/%.c, obj/%.o, $(SRC4))\
	$(patsubst src/exec/%.c, obj/%.o, $(SRC5))

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m

all: libft $(NAME)

#LINKING
$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(IFLAG) $^ -o $@ $(LIBFT) -lreadline
	@echo "${GREEN}Linked up."

#COMPILING
obj/%.o: src/%.c $(HEADER)
	@mkdir -p obj
	@$(CC) $(IFLAG) -c $< -o $@ 

obj/%.o: src/utils/%.c $(HEADER)
	@mkdir -p obj
	@$(CC) $(IFLAG) -c $< -o $@ 

obj/%.o: src/builtins/%.c $(HEADER)
	@mkdir -p obj
	@$(CC) $(IFLAG) -c $< -o $@ 

obj/%.o: src/tokens/%.c $(HEADER)
	@mkdir -p obj
	@$(CC) $(IFLAG) -c $< -o $@ 

obj/%.o: src/parser/%.c $(HEADER)
	@mkdir -p obj
	@$(CC) $(IFLAG) -c $< -o $@ 

obj/%.o: src/exec/%.c $(HEADER)
	@mkdir -p obj
	@$(CC) $(IFLAG) -c $< -o $@ 


clean:
	@echo "${YELLOW}Cleaning..."
	@rm -f obj/*.o
	@echo "${GREEN}Cleaned."

fclean: clean
	@echo "${YELLOW}Fcleaning..."
	@rm -f $(NAME)
	@echo "${GREEN}Fcleaned."

re: fclean all

.PHONY: minishell all clean fclean re
