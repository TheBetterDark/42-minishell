/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/13 16:50:21 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

// ------------------------------ INCLUDES ---------------------------------- //

# include "../libft/include/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

// ------------------------------ DEFINES ----------------------------------- //

# define HEREDOC_PROMPT "> "
# define SHELL_PROMPT "minishell$ "

# define ERR_CMD_NOT_FOUND "command not found"
# define ERR_OUT_OF_MEMORY "Memory error: out of memory"
# define ERR_UNCLOSED_QUOTES "Syntax error: unmatched quotes"

# define EXIT_MEMORY 12

// ------------------------------ ENUMS ------------------------------------- //

enum					e_type
{
	CMD,
	PIPE,
	RDR_IN,
	RDR_OUT,
	RDR_APPEND,
	RDR_HEREDOC,
	ARG,
	DELIM,
	IN_FILE,
	OUT_FILE,
	APPEND_FILE,
	EXIT_STAT,
	ERROR
};

// ------------------------------ STRUCTS ----------------------------------- //

typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;

typedef struct s_token
{
	char				*cont;			// token content
	t_token				*next;			// next token
	t_token				*prev;			// previous token
	int					type;			// token type
}						t_token;

typedef struct s_cmd
{
	char				**cmdv;			// command vector
	char				*eof;			// delimiter for heredoc
	int					e_len;			// end_of_file length
	char				*open_fn;		// input file
	char				*append_fn;		// append file
	char				*input_fn;		// output file
	int					input_fd;		// exec's input
	int					output_fd;		// exec's output
	int					pipefd[2];		// pipe fds
	pid_t				pid;			// process id
	t_cmd				*next;			// next command
}						t_cmd;

typedef struct s_data
{
	char				*input;			// user input
	t_token				*toks;			// token list
	char				**env;			// environment variables
	int					r_input_fd;		// read input file descriptor
	int					r_output_fd;	// read output file descriptor
	int					exit_stat;		// exit status
	t_cmd				*job;			// cmd list
}						t_data;

// ------------------------------ INITIALIZERS ------------------------------ //

t_data					*init_data(void);
void					cleanup_minishell(t_data *data);
void					exit_minishell(t_data *data, int exit_status);

// ------------------------------ SIGNALS ----------------------------------- //

int						initalize_signals(void);
void					handle_sigint(int sig);

// ---------------------------- TOKENIZER ----------------------------------- //

t_token					*tokenizer(t_data *data);
void					tok_redir_operator_type_assigner(t_token *head);
void					tok_redir_file_type_assigner(t_token *head);
void					tok_cmd_type_assigner(t_token *head);

t_token					*tok_lstnew(char *word);
void					tok_lstadd_back(t_token **head, t_token *new);
int						tok_lstsize(t_token *tok);
t_token					*tok_lstlast(t_token *tok);
void					tok_lstclear(t_token **tok);

char					**command_line_split(char *input, t_data *data);
int						count_words(const char *str);

// ------------------------------ PARSER ------------------------------------ //

t_cmd					*parser(t_data *data);
void					get_new_cmd_data(t_cmd *new_cmd, t_token *cur,
							t_data *data);

char					**init_cmdv(t_token *cur, int size, t_data *data);
char					*search_paths(char *path, char *cmd);
char					*dup_double_quotes(char *str, t_data *data);

// -------------------------------- EXECUTOR -------------------------------- //

void					executor(t_data *data);
bool					file_redirections(t_data *data, t_cmd *cmd);

void					write_heredoc(int heredoc, t_cmd *cmd);
void					direct_heredoc(t_data *d, t_cmd *cmd);

void					create_cmd_pipe(t_cmd *cmd);
void					close_pipe_ends(t_cmd *cmd);
void					connect_pipeline(t_cmd *cmd);

bool					check_for_builtins(t_data *data, t_cmd *cmd);
void					builtin_echo(t_cmd *cmd);
void					builtin_pwd(void);
void					builtin_cd(t_cmd *cmd);
void					builtin_env(t_data *data);
void					builtin_export(t_data *data, char *export_str);
void					builtin_unset(t_data *data, char *unset_str);

// ------------------------------ UTILS ------------------------------------- //

void					handle_error(t_data *data, char *msg, int err_num,
							bool exit);

bool					is_builtin_command(const char *command);
bool					input_matches(char *input, char *test);

char					*find_env_var(char *str, char **env);
char					*try_env_value(char *subquote, char **env,
							int exit_stat);

bool					is_quote(const char c, const char quote);
bool					is_blank(const char c);

#endif
