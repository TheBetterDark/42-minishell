/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:53:48 by muabdi            #+#    #+#             */
/*   Updated: 2024/11/21 18:04:28 by muabdi           ###   ########.fr       */
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

# ifndef PATH_MAXk
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
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_DELIMETER,
	TOKEN_PIPE,
	TOKEN_END
}						t_token_type;

// Structs

typedef struct s_lexer
{
	unsigned int		position;
	char				*input;
	char				cursor;
}						t_lexer;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	char				*path;
	char				**args;
	int					input_fd;
	int					output_fd;
	int					append_fd;
	char				*end_of_file;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char				hostname[HOST_NAME_MAX];
	char				cwd[PATH_MAX];
	char				*user;
	char				*input;

	t_command			**commands;
}						t_data;

// Functions

t_data					*initialize_shell(void);
int						initalize_signals(void);

int						ft_getcwd(char *cwd, bool is_tilde);
int						ft_gethostname(char *hostname);

#endif
