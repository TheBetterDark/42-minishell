/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 17:53:02 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/include/libft.h"
# define PROMPT "minishell$ "
# define SYNTAX_ERR1 "minishell: syntax error near unexpected token `<'\n"
# define SYNTAX_ERR2 "minishell: syntax error near unexpected token `newline'\n"

extern volatile sig_atomic_t	g_signal;

typedef struct s_token			t_token;
typedef struct s_cmd			t_cmd;
typedef struct s_rdr			t_rdr;
typedef struct s_hdc			t_hdc;

typedef enum e_type
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	COMMAND,
	ARG,
	FD,
	DELIMETER,
	FILENAME
}	t_type;

typedef struct s_token
{
	char	*cont;
	t_token	*next;
	int		pos;
	int		end_pos;
	t_type	type;
	bool	can_split;
}	t_token;

typedef struct s_rdr
{
	int		fd;
	int		o_fd;
	char	*fn;
	t_type	type;
	bool	if_rdr;
}	t_rdr;

typedef struct s_hdc
{
	int		fd;
	char	*eof;
	int		pipe[2];
}	t_hdc;

typedef struct s_cmd
{
	char	**args;
	t_rdr	*rdr;
	t_hdc	*hdc;
	int		rdr_ct;
	int		hdc_size;
	pid_t	pid;
	int		pipe[2];
	bool	if_executable;
}	t_cmd;

typedef struct s_mini
{
	struct termios	terminal;
	long long		exit_status;
	t_list			*env_vars; // *mem_env
	t_list			*mem;
	t_token			*t_head;
	t_token			*t_tail;
	t_cmd			*cmd;
	int				job_idx;
	int				job_size;
	bool			is_print_sig;
	char			*path;
	int				a_size;
	int				b_size;
	char			*input;
	int				env_size;
}	t_mini;

//loop
void	main_loop(t_mini *m);

//signal
void	init_signal(void);
void	end_shell(t_mini *m, int end_code);
void	handle_sigint(int signo);
void	handle_sigint_hdc(int signo);
void	sig_int(int signo);
void	sig_quit(int signo);
void	sig_ignore(void);
void	sig_default(t_mini *m);
void	config_terminal(t_mini *m);

//init
bool	init_minishell(t_mini *m);
bool	init_environment(t_mini *m);

//token
bool	tokenizer(t_mini *m);

//env
bool	get_env(t_mini *m, t_token *tok, bool is_div);

//parse
bool	parser(t_mini *m);

//execute
bool	executor(t_mini *m);
void	b_pwd(t_mini *m, bool is_print);
bool	is_parent(t_mini *m);

//for env
void	m_export(t_mini *m, char *new_env, char *caller);
void	m_unset(t_mini *m, char *target);
bool	env_size_inc(t_mini *m, char *new_str);
bool	env_size_dec(t_mini *m, char *target, int tar_len);
bool	is_exist_export(t_mini *m, char *target);
bool	get_env_str(t_mini *m, char **str);

#endif
