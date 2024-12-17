NAME	= minishell
CC		= cc -Wall -Wextra -Werror -g #-fsanitize=address
SRC		= $(wildcard src/*.c)
OBJ		= $(SRC:.c=.o)
OBJ		= $(patsubst src/%.c,obj/%.o,$(SRC))
HEADER	= $(wildcard inc/*.h) libft/include/libft.h
IFLAG	= -I./include
LIBFT	= libft/libft.a
LINKER	= -lreadline -ltermcap
VALG	= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

all: $(NAME) $(LIBFT)

$(LIBFT):
	@make -C libft/ all

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) $(LIBFT) $(IFLAG) -o $(NAME) $(LINKER)

obj/%.o: src/%.c $(HEADER)
	@mkdir -p obj
	@$(CC) -c $< -o $@ $(IFLAG)

valgrind: $(NAME)
	@$(VALG) ./$(NAME)


clean:
	@make -C ./libft clean
	@rm -f src/*.o
	@rm -rf obj
	@rm	-f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft minishell
