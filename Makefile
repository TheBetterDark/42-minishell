NAME 	= minishell 
CC		= cc -Wall -Wextra -Werror -g #-fsanitize=address
SRC		= $(wildcard src/*.c)
OBJ		= $(SRC:.c=.o)
OBJ		= $(patsubst src/%.c,obj/%.o,$(SRC))
HEADER	= $(wildcard inc/*.h) libft/include/libft.h
IFLAG	= -I./include
LIBFT	= libft/libft.a
LINKER = -lreadline -ltermcap

all: $(NAME) $(LIBFT)

$(LIBFT):
	@make -C libft/ all

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) $(LIBFT) $(IFLAG) -o $(NAME) $(LINKER)

obj/%.o: src/%.c $(HEADER)	
	@mkdir -p obj
	@$(CC) -c $< -o $@ $(IFLAG)

clean:
	@make -C ./libft clean
	@rm -f src/*.o
	@rm -rf obj
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft minishell 
