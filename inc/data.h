/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/17 13:12:14 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

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

typedef struct s_data	t_data;
typedef	struct s_token	t_token;
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
	
	t_cmd	*job;
}	t_data;

t_data	*init_data(char **environ);
void	free_data(t_data *d);
void	free_minishell(t_data *d);
void	readline_config(t_data *d);

//------------------------------------- TOKENIZER --------------------------------------------

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
	ERROR
};

typedef	struct s_token
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
void	tok_lstadd_back(t_token **head, t_token *new); // new_tok
int		tok_lstsize(t_token *tok);
t_token	*tok_lstlast(t_token *tok);
void	tok_lstclear(t_token **tok);

void	print_toks(t_data *d);
void	print_type(int type);

char	**get_paths();
bool	is_cmd(t_token *cur, bool first);
bool	is_pipe(t_token *cur);

//------------------------------------- PARSER -----------------------------------------------

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

void	print_job(t_cmd *job);

//------------------------------------- EXECUTOR ---------------------------------------------


//t_data	*init_data(int ac, char **av, char **env);
t_cmd	*init_job(char **av);
//t_cmd	*init_new_cmd(char *av);
void	add_to_job(t_cmd **head_cmd, t_cmd *new_cmd);
char	*check_null(char *av);
void	add_to_job(t_cmd **head_cmd, t_cmd *new_cmd);
void	print_job(t_cmd *job);
void	free_job(t_cmd *job);

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


void	check_for_builtins(t_data *d, t_cmd *cur);
bool	input_matches(char *input, char *test);

void	skyy_echo(t_cmd *cur);
void	skyy_pwd();
void	skyy_cd(t_cmd *cur);
void	skyy_env(t_data *d);
void	skyy_export(t_data *d, char *export_str);
void	skyy_unset(t_data *d, char *unset_str);

void	print_str_arr(char **str_arr);

#endif
