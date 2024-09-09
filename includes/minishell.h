/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:53:48 by muabdi            #+#    #+#             */
/*   Updated: 2024/09/09 19:53:23 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Standard Libraries

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Custom Libraries

# include "../libs/libft/includes/libft.h"

// Macros

# ifndef HOST_NAME_MAX
#  define HOST_NAME_MAX 256
# endif

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define RST "\001\033[0;39m\002" // Reset
# define USR "\001\033[1;92m\002" // Green
# define CWD "\001\033[1;94m\002" // Blue
# define ERR "\001\033[1;91m\002" // Red
# define INF "\001\033[1;96m\002" // Cyan
# define WRN "\001\033[1;95m\002" // Magenta
# define DEF "\001\033[0;97m\002" // White

// Enums

typedef enum e_token_type
{
	TOKEN_CMD,
	TOKEN_ARG,
	TOKEN_TRUNCATE,
	TOKEN_APPEND,
	TOKEN_INPUT,
	TOKEN_PIPE,
	TOKEN_END
}					t_token_type;

// Structs

typedef struct s_lexer
{
	unsigned int	position;
	char			*input;
	char			cursor;
}					t_lexer;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_command
{
	int				num_of_args;
	char			*path;
	char			**args;
}					t_command;

typedef struct s_data
{
	char			hostname[HOST_NAME_MAX];
	char			cwd[PATH_MAX];
	char			*user;

	char			*input;

	t_command		**commands;
	char			*out_file;
	char			*in_file;
	char			*err_file;
}					t_data;

// Functions

t_data				*initialize_shell(void);
// int					initalize_signals(void);

t_token				*token_new(t_token_type type, char *value);
void				token_append(t_token **tokens, t_token *new);
void				token_cleanup(t_token **tokens);

t_token				*handle_greater(t_lexer *lexer);
t_token				*handle_less(t_lexer *lexer);
t_token				*handle_single_quote(t_lexer *lexer);
t_token				*handle_double_quote(t_lexer *lexer);
t_token				*handle_pipe(t_lexer *lexer);

t_command			*command_new(char *path, char **args);
void				command_append(t_command ***commands, t_command *new);
void				command_cleanup(t_command **commands);

t_lexer				*lexer_init(char *input);
void				lexer_advance(t_lexer *lexer);
t_token				*lexer_get_next_token(t_lexer *lexer);
t_token				*lexer_tokenize(char *input);
void				lexer_cleanup(t_lexer *lexer);

int					ft_getcwd(char *cwd, bool is_tilde);
int					ft_gethostname(char *hostname);

#endif
