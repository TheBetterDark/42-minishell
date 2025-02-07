NAME 	= libft.a
CC		= cc -Wall -Wextra -Werror -g
SRC		= $(wildcard src/*.c)
#SRC 	= $(addprefix src/, ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c  ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c get_next_line_utils.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_printf.c hex_utils.c ptr_utils.c unsigned_utils.c)
OBJ 	= $(SRC:.c=.o)
HEADER 	= include/libft.h

NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ) 
	@echo $(GREEN) "Libft Compiled"$(NONE)
	@rm $(OBJ)

%.o: %.c $(HEADER) 
	@$(CC) -c $< -o $@ 

clean:
	@rm -f $(OBJ)

fclean: clean 
	@rm -f $(NAME)

re: fclean all

main:
	@$(CC) main.c $(LFLAG) -o main

mclean: fclean clean
	@rm -f main

.PHONY: all clean fclean re
