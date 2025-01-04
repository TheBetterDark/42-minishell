/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/04 16:27:56 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

// ------------------------------ INCLUDES ---------------------------------- //

# include "../libft/include/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/stat.h>
# include <fcntl.h>

// ------------------------------ STRUCTS ----------------------------------- //

typedef struct s_data	t_data;
typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;

typedef struct s_data
{
	char	*input;
	int		cmd_ct;
	t_token	*toks;
//
	char	**env;
	int		input_fd;
	int		output_fd;
	int		r_input_fd;
	int		r_output_fd;
	int		pipefd[2];
	int		exit_stat;
	t_cmd	*job;
}	t_data;

// ------------------------------ FUNCTIONS --------------------------------- //

t_data	*init_data(char **environ);
void	free_data(t_data *d);
void	free_minishell(t_data *d);

// ---------------------------- TOKENIZER ----------------------------------- //

enum e_type
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
	char			*cont;
	t_token			*next;
	t_token			*prev;
	int				type;
}	t_token;

t_token	*tokenizer(t_data *d);
void	assign_one_type(t_token *tok, int *type);
void	assign_multiple_type(char *tk, int *type);
void	tok_preliminary_type_assigner(t_token *head, t_data *d);
void	tok_secondary_type_assigner(t_token *head);

char	**get_paths(void);

t_token	*tok_lstnew(char *word);
void	tok_lstadd_back(t_token **head, t_token *new);
int		tok_lstsize(t_token *tok);
t_token	*tok_lstlast(t_token *tok);
void	tok_lstclear(t_token **tok);

void	print_toks(t_data *d);
void	print_type(int type);

char	**get_paths(void);
bool	is_cmd(t_token *cur, bool first);
char	**command_line_split(char *input);
int		find_char_pos(const char *str, char target);
bool	is_quote(const char c, const char quote);
bool	is_blank(const char c);
int		handle_quote(const char *str, char quote);
int		count_words(const char *str);

// ------------------------------ PARSER ------------------------------------ //

typedef struct s_cmd
{
	char	**cmdv;
	char	*eof; // delimiter for heredoc
	int		e_len; // eof_len
	char	*open_fn;
	char	*append_fn;
	char	*input_fn;
	t_cmd	*next;
}	t_cmd;

t_cmd	*init_new_cmd(t_token **cur, t_data *d);
void	add_to_job(t_cmd **head_cmd, t_cmd *new_cmd);
t_cmd	*parser(t_data *d);
int		find_cmdv_size(t_token *cur);
char	**init_cmdv(t_token *cur, int size, t_data *d);
void	set_new_cmd_nulls(t_cmd *new_cmd);
void	get_new_cmd_data(t_cmd *new_cmd, t_token *cur, t_data *d);
char	*add_path_to_cmdv0(char *cmd);
char	**get_paths(void);
void	free_paths(char **paths);
char	*search_paths(char *path, char *cmd);
void	cleanup_job(t_cmd *job);
char	*dup_double_quotes(char *str, t_data *d);
void	safe_free(void **ptr);

// -------------------------------- EXECUTOR -------------------------------- //

void	executor(t_data *d);
void	add_to_job(t_cmd **head_cmd, t_cmd *new_cmd);

void	redirect_child_fds(t_data *d);
void	fork_child_process(t_data *d, t_cmd *cur);
void	create_child_pipe(t_data *d);
void	execute_child_program(t_data *d, t_cmd *cur);

void	close_pipe_ends(t_data *d);
void	check_for_open_redirect(t_data *d, t_cmd *cur);
void	check_for_append_redirect(t_data *d, t_cmd *cur);

void	direct_output(t_data *d, t_cmd *cur);
void	direct_pipe_input(t_data *d);
void	direct_input(t_data *d, t_cmd *cur);
void	write_heredoc(int heredoc, t_cmd *cur);
void	direct_heredoc(t_data *d, t_cmd *cur);
void	execute_parent_process(t_data *d, t_cmd *cur);

bool	check_for_builtins(t_data *d, t_cmd *cur);
bool	input_matches(char *input, char *test);

void	skyy_echo(t_cmd *cur);
void	skyy_pwd(void);
void	skyy_cd(t_cmd *cur);
void	skyy_env(t_data *d);
void	skyy_export(t_data *d, char *export_str);
void	skyy_unset(t_data *d, char *unset_str);

void	file_redirections(t_data *d, t_cmd *cur);
void	catch_exit_status(pid_t pid, t_data *d);

#endif
