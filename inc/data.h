/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/24 16:29:12 by smoore           ###   ########.fr       */
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
# define SHELL_PROMPT "minishell-$ "

# define ERR_OUT_OF_MEMORY "Memory error: out of memory"
# define ERR_UNCLOSED_QUOTES "Syntax error: unmatched quotes"

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
typedef struct s_in		t_in;
typedef struct s_out	t_out;

typedef struct s_token
{
	char				*cont;			// token content
	t_token				*next;			// next token
	t_token				*prev;			// previous token
	int					type;			// token type
}						t_token;

typedef struct s_in
{
	char				*eof;			// delimiter
	int					eof_len;		// delimiter length
	int					pipe_fds[2];	// heredoc pipe_fds
	pid_t				pid;			// process id
	int					heredoc_fd;		// heredoc fildes
	char				*read_fn;		// input file
	struct s_in			*next;
}	t_in;

typedef struct s_out
{
	char				*truc_fn;		// filename for truc file
	char				*append_fn;		// filename for append file
	struct s_out		*next;
}	t_out;

typedef struct s_cmd
{
	char				**cmdv;			// command vector
	t_in				*ins;			// in redirections
	t_out				*outs;			// out redirections
	pid_t				pid;			// process id
	int					i;				// index of pipe_fds
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
	int					cmd_ct;			// cmd count for pipe_fds
	bool				first_cmd;
	int					**pipe_fds;		// to allocate pipes
	int					pipe_ct;		// size of pipes
	int					save_stdout;
	int					save_stdin;
}						t_data;

// ------------------------------ INITIALIZERS ------------------------------ //

t_data					*init_data(void);
void					cleanup_minishell(t_data *data);
void					exit_minishell(t_data *data, int exit_status);

// ------------------------------ SIGNALS ----------------------------------- //

void					initalize_signals(void);
void					handle_sigint(int sig);
void					handle_sigint_child(int sig);

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
bool					is_redir_symbol(char c);

// ------------------------------ PARSER ------------------------------------ //

t_cmd					*parser(t_data *data);
char					*handle_filename(t_token *cur, int type, char *rdr);
void					get_new_cmd_data(t_cmd *new_cmd, t_token *cur,
							t_data *data);

char					**init_cmdv(t_token *cur, int size, t_data *data);
char					*search_paths(char *path, char *cmd);
char					*dup_double_quotes(char *str, t_data *data);
void					add_in_redir(t_in **head, t_in *new);
t_in					*new_in_redir(t_token *cur);
//t_in					*init_in_redirections(t_token *cur);
t_in					*init_in_redirections(t_in **head, t_token *cur);
void					clear_in_list(t_in **head);
void					add_out_redir(t_out **head, t_out *new);
t_out					*new_out_redir(t_token *cur);
t_out					*init_out_redirections(t_out **head, t_token *cur);
//t_out					*init_out_redirections(t_token *cur);
void					clear_out_list(t_out **head);

// -------------------------------- EXECUTOR -------------------------------- //

void					executor(t_data *data);
bool					file_redirections(t_data *data, t_cmd *cmd);
bool					infile_redirections(t_data *data, t_in *in);
bool					outfile_redirections(t_data *data, t_out *out);

//void					direct_heredoc(t_data *d, t_cmd *cmd);
int						direct_heredoc(t_data *data, t_in *in, int *heredoc_count);
void					traverse_heredocs(t_data *data, t_cmd *cmd);

void					init_pipes(t_data *data, int cmd_ct);
void					close_pipes(t_data *data, int cmd_ct);
void					redirect_child_stdio(t_data *data, int *i, int pipe_ct);
void					free_pipes(t_data *data, int pipe_ct);

bool					check_for_builtins(t_data *data, t_cmd *cmd);
void					builtin_echo(t_cmd *cmd);
void					builtin_pwd(void);
void					builtin_cd(t_cmd *cmd);
void					builtin_env(t_data *data);
void					builtin_export(t_data *data, char *export_str);
void					builtin_unset(t_data *data, char *unset_str);

// ------------------------------ UTILS ------------------------------------- //

void					handle_error_parent(t_data *data, char *msg,
							int err_num, bool exit_stat);
void					handle_error_child(t_data *data, char *msg,
							int err_num, bool exit_stat);
void					handle_command_not_found(t_data *data,
							char *command_name);

bool					is_builtin_command2(const char *command);
bool					is_builtin_command(t_data *data);
bool					input_matches(char *input, char *test);

char					*find_env_var(char *str, char **env);
char					*extract_env_var(const char *str);
char					*try_env_value(char *subquote, char **env,
							int exit_stat);

bool					is_quote(const char c, const char quote);
bool					is_blank(const char c);
void					unlink_heredocs(t_cmd *cmd);

#endif
