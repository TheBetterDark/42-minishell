# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 23:59:26 by muabdi            #+#    #+#              #
#    Updated: 2024/08/18 22:08:22 by muabdi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INCLUDES = ./includes

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g3
INCLUDEFLAGS = -I$(INCLUDES)

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
	@echo "${YELLOW}Creating $(NAME)...${NC}"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "${GREEN}$(NAME) created.${NC}"

all: $(NAME) $(OBJ_DIR)

clean:
	@echo "${YELLOW}Removing object files...${NC}"
	@rm -rf $(OBJ_DIR)
	@echo "${GREEN}Object files removed.${NC}"

fclean: clean
	@echo "${YELLOW}Removing $(Name) executable...${NC}"
	@rm -f $(NAME)
	@echo "${GREEN}$(NAME) executable removed.${NC}"

re: fclean all

libs:
	@echo "${YELLOW}Updating submodules...${NC}"
	@git submodule update --init --recursive --remote
	@echo "${GREEN}Submodules updated.${NC}"

.PHONY: all clean fclean re libs
