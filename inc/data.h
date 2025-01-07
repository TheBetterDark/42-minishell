/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/07 22:55:27 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

// ------------------------------ INCLUDES ---------------------------------- //

# include "../libft/include/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

// ------------------------------ STRUCTS ----------------------------------- //

typedef struct s_data	t_data;
typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;

typedef struct s_data
{
	char				*input;
	int					cmd_ct;
	t_token				*toks;
	//
	char				**env;
	int					input_fd;
	int					output_fd;
	int					r_input_fd;
	int					r_output_fd;
	int					pipefd[2];
	int					exit_stat;
	t_cmd				*job;
}						t_data;

// ------------------------------ FUNCTIONS --------------------------------- //

t_data					*init_data(char **environ);
void					free_data(t_data *d);
void					free_minishell(t_data *d);
void					handle_sigint(int sig);

// ---------------------------- TOKENIZER ----------------------------------- //

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

typedef struct s_token
{
	char				*cont;
	t_token				*next;
	t_token				*prev;
	int					type;
}						t_token;

t_token					*tokenizer(t_data *d);
void					tok_preliminary_type_assigner(t_token *head, t_data *d);
void					tok_secondary_type_assigner(t_token *head);

char					**get_paths(t_data *d);

t_token					*tok_lstnew(char *word);
void					tok_lstadd_back(t_token **head, t_token *new);
int						tok_lstsize(t_token *tok);
t_token					*tok_lstlast(t_token *tok);
void					tok_lstclear(t_token **tok);

bool					is_cmd(t_token *cur, bool first);
char					**command_line_split(char *input, t_data *d);
int						find_char_pos(const char *str, char target);
bool					is_quote(const char c, const char quote);
bool					is_blank(const char c);
int						handle_quote(const char *str, char quote);
int						count_words(const char *str);

// ------------------------------ PARSER ------------------------------------ //

typedef struct s_cmd
{
	char				**cmdv; // command vector
	char				*eof; // delimiter for heredoc
	int					e_len; // end_of_file length
	char				*open_fn; // input file
	char				*append_fn; // append file
	char				*input_fn; // output file
	pid_t				pid; // process id
	t_cmd				*next; // next command
}						t_cmd;

t_cmd					*init_new_cmd(t_token **cur, t_data *d);
void					add_to_job(t_cmd **head_cmd, t_cmd *new_cmd);
t_cmd					*parser(t_data *d);
int						find_cmdv_size(t_token *cur);
char					**init_cmdv(t_token *cur, int size, t_data *d);
void					set_new_cmd_nulls(t_cmd *new_cmd);
void					get_new_cmd_data(t_cmd *new_cmd, t_token *cur,
							t_data *d);
void					free_paths(char **paths);
char					*search_paths(char *path, char *cmd);
char					*dup_double_quotes(char *str, t_data *d);
bool					terms_match(char *str1, char *str2);
void					cleanup_job(t_cmd *job);
char					*get_key(char *str);
char					*find_env_var(char *str, char **env);
char					*try_env_value(char *subquote, char **env,
							int exit_stat);

// -------------------------------- EXECUTOR -------------------------------- //

void					executor(t_data *d);
void					add_to_job(t_cmd **head_cmd, t_cmd *new_cmd);

void					redirect_child_fds(t_data *d);
void					fork_child_process(t_data *d, t_cmd *cur);
void					create_child_pipe(t_data *d);
void					execute_child_program(t_data *d, t_cmd *cur);

void					close_pipe_ends(t_data *d);
void					check_for_open_redirect(t_data *d, t_cmd *cur);
void					check_for_append_redirect(t_data *d, t_cmd *cur);

void					direct_output(t_data *d, t_cmd *cur);
void					direct_pipe_input(t_data *d);
void					direct_input(t_data *d, t_cmd *cur);
void					write_heredoc(int heredoc, t_cmd *cur);
void					direct_heredoc(t_data *d, t_cmd *cur);
void					execute_parent_process(t_data *d, t_cmd *cur);

bool					check_for_builtins(t_data *d, t_cmd *cur);
bool					input_matches(char *input, char *test);

void					skyy_echo(t_cmd *cur);
void					skyy_pwd(void);
void					skyy_cd(t_cmd *cur);
void					skyy_env(t_data *d);
void					skyy_export(t_data *d, char *export_str);
void					skyy_unset(t_data *d, char *unset_str);

void					file_redirections(t_data *d, t_cmd *cur);
void					catch_exit_status(pid_t pid, t_data *d);

#endif
