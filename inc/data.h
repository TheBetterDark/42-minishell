/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:45:05 by smoore            #+#    #+#             */
/*   Updated: 2025/02/19 18:14:03 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "../libft/include/libft.h"
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define NL_ERR "minishell: syntax error near unexpected token `newline'\n"
# define PIPE_ERR "minishell: syntax error near unexpected token `| '\n"
# define CON_ERR "\nminishell: unexpected EOF while looking for matching \"\'\n"
# define CON_ERR2 "minishell: syntax error: unexpected end of file\n"

extern volatile sig_atomic_t	g_signal;

enum							e_type
{
	ARG,
	CMD,
	PIPE,
	RE_READ,
	RE_TRUNC,
	RE_APPEND,
	RE_HEREDOC,
	FN_READ,
	FN_TRUNC,
	FN_APPEND,
	DELIM,
};

enum							e_signal
{
	NO_SIGNAL,
	RL_SIGNAL,
	NORMAL_SIGNAL,
	IGNORE_SIGNAL,
	HEREDOC_SIGNAL,
	CHILD_SIGNAL,
	PARENT_SIGNAL
};

typedef struct s_data			t_data;
typedef struct s_token			t_token;
typedef struct s_cmd			t_cmd;
typedef struct s_ins			t_ins;
typedef struct s_outs			t_outs;

typedef struct s_ins
{
	char			*read_fn;
	char			*eof;
	bool			eof_quoted;
	int				eof_len;
	int				fd;
	t_ins			*next;
}	t_ins;

typedef struct s_outs
{
	char			*trunc_fn;
	char			*append_fn;
	t_outs			*next;
}	t_outs;

typedef struct s_cmd
{
	char			**cmdv;
	t_ins			*ins;
	t_outs			*outs;
	pid_t			pid;
	int				i;
	t_cmd			*next;
}	t_cmd;

typedef struct s_token
{
	char			*str;
	t_token			*next;
	t_token			*prev;
	int				type;
}	t_token;

typedef struct s_data
{
	char			*input;
	struct termios	saved_termios;
	int				exit_stat;
	t_token			*toks;
	char			**env;
	t_cmd			*cmds;
	int				pipe_ct;
	int				cmd_ct;
	int				heredoc_ct;
	int				saved_stdin;
	int				saved_stdout;
	int				**pipe_fd;
	int				read_fd;
	int				write_fd;
	char			*pwd;
	bool			token_syntax_error;
	bool			input_mode;
	bool			prompt_cont_error;
}	t_data;

//	** MAIN  **	//
char	*read_command_line(t_data *data);
void	run_minishell(t_data *data);

//	** UTILS INIT/STRS/SIGNALS **	//

void	free_minishell(t_data *data);
t_data	*initialize_minishell(void);

bool	word_match(char *word, char *check);
bool	is_blank(char c);
bool	is_symbol(char c);
bool	is_quote(char c);
bool	is_ascii_symbol(char c);

int		quoted_strlen(char *str);

bool	has_quotes(char *str);
bool	calculate_if_finished(int single_quotes, int double_quotes);
bool	has_finished_quotes(char *str);
char	get_first_quote(char *input);

char	*finish_quotes(char *input);

void	child_sigquit_handler(int signo);
void	parent_sigquit_handler(int signo);
void	modify_sigquit(int state);
void	init_termios(t_data *data);

void	rl_sigint_handler(int signo);
void	normal_sigint_handler(int signo);
void	child_sigint_handler(int signo);
void	heredoc_sigint_handler(int signo);
void	modify_sigint(int state, t_data *data);

char	*complete_quoted_input(char *input);
char	*append_symbols_dbl(char *expand, char *name, int *i);

//	**TOKENIZE**	//
void	tokenize(t_data *data);
char	**command_line_split(char *line);
int		count_words(char *line);
char	**allocate_words_memory(char *line);

void	tok_lstclear(t_token **head);
void	tok_lstadd_back(t_token **head, t_token *new);
t_token	*tok_lstlast(t_token *cur);
t_token	*tok_lstnew(char *word);

void	assign_tok_types(t_token *head, t_data *data);

void	unexpected_token_error(t_token *head, t_data *data);
void	check_for_redir_files(t_token *head, t_data *data);
void	check_for_final_cmd(t_token *head, t_data *data);
void	get_next_input(t_data *data);

bool	check_redir_file_error(t_token *symbol, t_token *file);

//	**PARSE**	//
void	parse(t_data *data);

void	cmd_lstclear(t_cmd **head);
void	cmd_lstadd_back(t_cmd **head, t_cmd *new);
t_cmd	*cmd_lstnew(t_token **cur, t_data *data);

int		find_cmdv_size(t_token *toks);
char	**get_cmdv(t_token *toks, int size);

//void	get_io_redirs(t_cmd *cmd, t_token *toks, t_data *data);
void	get_io_redirs(t_cmd **cmd, t_token *toks, t_data *data);

void	ins_lstclear(t_ins **head);
void	ins_lstadd_back(t_ins **head, t_ins *new);
t_ins	*ins_lstnew(t_token *cur, t_data *data);

void	outs_lstclear(t_outs **head);
void	outs_lstadd_back(t_outs **head, t_outs *new);
t_outs	*outs_lstnew(t_token *cur);

void	expand_ins(t_ins **in, t_data *data);
void	expand_outs(t_outs **outs, t_data *data);
void	expand_cur_cmds(t_cmd *cmd, t_data *data);
void	get_expansions(t_cmd **cmds, t_data *data);

char	*handle_single_quotes(char *name, int *i);
char	*handle_double_quotes(char *name, int *i, t_data *data);
char	*handle_non_quotes(char *name, int *i, t_data *data);
char	*process_substr(char *name, int *i, t_data *data);
char	*process_str(char *name, t_data *data);

char	*get_plain_substr(char *name, int *i);
char	*get_expanded_substr(char *substr, int *i, t_data *data);
char	*get_expanded_substr_dbl(char *name, int *i, t_data *data);
char	*try_expand_dup(char *substr, t_data *data, bool dbl); // bool dbl

char	*get_environment_variable(char *env_var, t_data *data);
char	*find_env_match(char *key, char **env);
void	print_env(t_data *data);

char	*get_key(char *env_cur);
char	*search_for_env_match(char *key, char **env);
char	*find_environment_value(char *key, t_data *data);

bool	is_builtin_cmd_child(char *cmdv);
bool	is_builtin_cmd_parent(char *cmdv);
char	*add_path_cmdv0(char **cmdv0, t_data *data);
char	*search_paths(char *path, char *cmd);

void	get_heredocs(t_cmd **cmds, t_data *data);

//	** BUILTINS **	//
void	builtin_cd(t_data *data, t_cmd *cmd);
void	builtin_echo(t_cmd *cmd);
void	builtin_env(t_data *data);
void	builtin_exit(t_data *data);
void	builtin_export(t_data *data, char **export_str);
void	builtin_pwd(t_data *data);
void	builtin_unset(t_data *data, char **unset_str);
void	execute_builtin(t_data *data, char *cmd);

//	** EXECUTE **	//

void	parent_waits_for_child(t_data *data, t_cmd *cur);
void	execve_child(t_data *data, t_cmd *cur);
void	prepare_pipeline(t_data *data, t_cmd *cmds);
void	select_process(t_data *data);
void	execute(t_data *data);

void	open_read_files(t_ins *in, t_data *data);
void	open_write_files(t_outs *outs, t_data *data);
void	open_files(t_cmd *cmd, t_data *data);
void	prepare_file_descriptors(t_data *data, t_cmd *cur);

void	init_pipes(t_data *data, int pipe_ct);
void	close_pipes(t_data *data, int pipe_ct);
void	free_pipes(t_data *data, int pipe_ct);
void	redirect_pipes(t_data *data, int i);

void	cleanup_child(t_data *data, int exit_status);

#endif
