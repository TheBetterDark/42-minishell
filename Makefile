# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 23:59:26 by muabdi            #+#    #+#              #
#    Updated: 2024/08/25 18:41:51 by muabdi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDES = ./includes
LIBS = ./libs

LIBFT = $(LIBS)/libft

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
INCLUDEFLAGS = -I$(INCLUDES) -I$(LIBFT)/includes

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

SRC_DIR = ./src
OBJ_DIR = ./bin

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME) $(OBJ_DIR)

$(OBJ_DIR):
	@echo "${YELLOW}Creating object directory $(OBJ_DIR)...${NC}"
	@mkdir -p $(OBJ_DIR)
	@echo "${GREEN}Object directory $(OBJ_DIR) created.${NC}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDEFLAGS) -c $< -o $@

${NAME}: $(OBJS)
	@make -C $(LIBFT)
	@echo "${YELLOW}Creating $(NAME)...${NC}"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -o $(NAME) -lreadline
	@echo "${GREEN}$(NAME) created.${NC}"

all: $(NAME) $(OBJ_DIR)

clean:
	@make -C $(LIBFT) clean
	@echo "${YELLOW}Removing object files...${NC}"
	@rm -rf $(OBJ_DIR)
	@echo "${GREEN}Object files removed.${NC}"

fclean:
	@make -C $(LIBFT) fclean
	@echo "${YELLOW}Removing object files...${NC}"
	@rm -rf $(OBJ_DIR)
	@echo "${GREEN}Object files removed.${NC}"
	@echo "${YELLOW}Removing $(Name) executable...${NC}"
	@rm -f $(NAME)
	@echo "${GREEN}$(NAME) executable removed.${NC}"

re: fclean all

libs:
	@echo "${YELLOW}Updating submodules...${NC}"
	@git submodule update --init --recursive --remote
	@echo "${GREEN}Submodules updated.${NC}"

leaks: all
	valgrind --suppressions=valgrind.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re libs
