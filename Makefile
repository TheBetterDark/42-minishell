# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 11:51:31 by smoore            #+#    #+#              #
#    Updated: 2025/02/19 15:10:00 by smoore           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDES = ./inc

LIBFT = libft

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

INCLUDEFLAGS = -I$(INCLUDES) -I$(LIBFT)/includes

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

SRC_DIR = ./src
OBJ_DIR = ./bin

SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/builtins/builtin_cd.c \
	$(SRC_DIR)/builtins/builtin_echo.c \
	$(SRC_DIR)/builtins/builtin_env.c \
	$(SRC_DIR)/builtins/builtin_exit.c \
	$(SRC_DIR)/builtins/builtin_export.c \
	$(SRC_DIR)/builtins/builtin_pwd.c \
	$(SRC_DIR)/builtins/builtin_unset.c \
	$(SRC_DIR)/builtins/execute_builtins.c \
	$(SRC_DIR)/exec/cleanup_child.c \
	$(SRC_DIR)/exec/execute.c \
	$(SRC_DIR)/exec/pipeline.c \
	$(SRC_DIR)/exec/prepare_file_descriptors.c \
	$(SRC_DIR)/parser/add_path_to_cmdv0.c \
	$(SRC_DIR)/parser/cmd_lstnew.c \
	$(SRC_DIR)/parser/find_cmdv_size.c \
	$(SRC_DIR)/parser/find_environment_value.c \
	$(SRC_DIR)/parser/get_expansions.c \
	$(SRC_DIR)/parser/get_heredocs.c \
	$(SRC_DIR)/parser/get_io_redirs.c \
	$(SRC_DIR)/parser/ins_lstnew.c \
	$(SRC_DIR)/parser/is_builtin_cmd.c \
	$(SRC_DIR)/parser/outs_lstnew.c \
	$(SRC_DIR)/parser/parse.c \
	$(SRC_DIR)/parser/process_str.c \
	$(SRC_DIR)/parser/search_paths.c \
	$(SRC_DIR)/parser/try_expand_dup.c \
	$(SRC_DIR)/parser/get_expanded_substr_dbl.c \
	$(SRC_DIR)/tokens/assign_tok_types.c \
	$(SRC_DIR)/tokens/check_redir_file_error.c \
	$(SRC_DIR)/tokens/token_error.c \
	$(SRC_DIR)/tokens/get_next_input.c \
	$(SRC_DIR)/tokens/command_line_split.c \
	$(SRC_DIR)/tokens/count_words.c \
	$(SRC_DIR)/tokens/tok_lstnew.c \
	$(SRC_DIR)/tokens/tokenize.c \
	$(SRC_DIR)/utils/init_free_data.c \
	$(SRC_DIR)/utils/finish_quotes.c \
	$(SRC_DIR)/utils/finish_quotes2.c \
	$(SRC_DIR)/utils/quote_strlen.c \
	$(SRC_DIR)/utils/str_utils.c \
	$(SRC_DIR)/utils/str_utils2.c \
	$(SRC_DIR)/utils/init_termios.c \
	$(SRC_DIR)/utils/sigint_handlers.c \
	$(SRC_DIR)/utils/env_util.c

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

.PHONY: all clean fclean re
