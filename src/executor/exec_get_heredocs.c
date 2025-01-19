/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/19 19:52:15 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static void	heredoc_sigint(int sig)
{
//	g_signal = signo;
	(void)sig;
	printf("\n");
	exit(EXIT_FAILURE);
}

bool	check_syntax(int single_quotes, int double_quotes, int len)
{
	if (!single_quote && !double_quote)
		return (true);
	if (single_quote == 1 || double_quote == 1)
		return (false);
	if ((single_quote == 2 && double_quote == 0)
		|| (single_quote == 0 && double_quote == 2))
	{
		if ((eof[len] == '\'' && eof[len - 1] == '\'')
			|| (eof[len] == '\"' && eof[len - 1] == '\"'))
			return (true);
	}
	return (false);
}

bool	is_valid_delim(char *eof)
{
	int		single_quotes;
	int		double_quotes;
	int		len;
	bool	result;

	result = true;
	single_quotes = 0;
	double_quotes = 0;
	len = ft_strlen(eof);
	while (*eof)
	{
		if (*eof == '\'')
			single_quote++;
		if (*eof == '\"')
			double_quote++;
		eof++;
	}
	result = check_syntax(single_quotes, double_quotes, len);
	return (result);
}

void	begin_heredoc_with_delimiter(t_data *data, t_cmd *cur_cmd)
{
	ft_putstr_fd("> ", STDOUT_FILENO);
	buf = get_next_line(STDIN_FILENO);
	buf_toks = ft_split(buf, ' ');
	while (*buf_toks)
	{
		save = buf;
		*buf_toks = try_env_value(*buf_toks, data->env, data->exit_stat);
		buf = ft_strjoin(save, *buf_toks);
		buf_toks++;
	}
	close(cur->pipe_fds[0]);
	ft_putstr_fd(buf, cur->pipe_fds[1]);
	free(buf);
}

void	check_delimiter(t_data *data, t_cmd *cur_cmd)
{
	char *buf;

	if (is_valid_delim(cur_cmd->ins->eof))
		begin_heredoc_with_delim(data, cur_cmd);
	else
	{
		while (true)
		{
			ft_putstr("> ", STDOUT_FILENO);
			buf = get_next_line(STDIN_FILENO);
			free(buf);
		}
	}
}

void	get_heredocs(t_data *data, t_cmd *cur_cmd)
{
	t_ins	*cur;	
	pid_t	pid;
	int		wstatus;
	char	**buf_toks;
	char	*buf;
	char	*save;

	if (!cur_cmd->ins)
		return ;
	cur = cur_cmd->ins;
	while (cur)
	{
		if (cur->eof)
		{
			pipe(cur->pipe_fds);
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, heredoc_sigint);
				check_delimiter(data, cur);
			}
		}
		else
			waitpid(pid, &wstatus, NULL);
		cur = cur->next;
	}
}
