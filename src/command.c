/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 17:26:58 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

char	**get_path(t_mini *m, char *cmd)
{
	char	*tmp;
	char	**ans;
	int		i;

	ans = ft_split(getenv("PATH"), ':');
	if (!ans)
		return (NULL);
	ft_lstlast(m->mem)->next = ft_lstnew(ans);
	i = 0;
	while (ans[i])
	{
		tmp = ans[i];
		ans[i] = ft_strjoin(tmp, "/");
		if (!ans)
			return (NULL);
		free(tmp);
		tmp = ans[i];
		ans[i] = ft_strjoin(tmp, cmd);
		if (!ans)
			return (NULL);
		ft_lstlast(m->mem)->next = ft_lstnew(ans[i]);
		free(tmp);
		i++;
	}
	return (ans);
}

static void	apply_redirect(t_mini *m, int idx)
{
	int		i;

	i = 0;
	while (i < m->cmd[idx].rdr_ct)
	{
		if (m->cmd[idx].rdr[i].if_rdr)
		{
			if (dup2(m->cmd[idx].rdr[i].o_fd, m->cmd[idx].rdr[i].fd) == -1)
			{
				perror("minishell");
				exit(errno);
			}
		}
		else
			m->cmd[idx].if_executable = 0;
		i++;
	}
	m->exit_status = 0;
}

void	child_processes(t_mini *m, int idx)
{
	sig_default(m);
	if (idx > 0)
		close(m->cmd[idx - 1].pipe[1]);
	if (idx != m->job_size - 1)
		close(m->cmd[idx].pipe[0]);
	if (idx != m->job_size - 1)
	{
		dup2(m->cmd[idx].pipe[1], STDOUT_FILENO);
		close(m->cmd[idx].pipe[1]);
	}
	if (idx != 0)
	{
		dup2(m->cmd[idx - 1].pipe[0], STDIN_FILENO);
		close(m->cmd[idx - 1].pipe[0]);
	}
	apply_redirect(m, idx);
	if (m->cmd[idx].hdc_size)
	{
		dup2(m->cmd[idx].hdc[m->cmd[idx].hdc_size - 1].pipe[0], STDIN_FILENO);
		close(m->cmd[idx].hdc[m->cmd[idx].hdc_size - 1].pipe[0]);
		close(m->cmd[idx].hdc[m->cmd[idx].hdc_size - 1].pipe[1]);
	}
	if (m->cmd[idx].if_executable)
		execute_cmd(m, idx);
	exit(1);
}

void	parent_process(t_mini *m)
{
	apply_redirect(m, 0);
	if (m->cmd[0].hdc_size)
		dup2(m->cmd[0].hdc[m->cmd[0].hdc_size - 1].pipe[0], STDIN_FILENO);
	execute_builtin(m, 0, 1);
}

bool	is_command(t_mini *m)
{
	int		i;

	i = -1;
	while (++i < m->job_size)
	{
		if (create_pipe_for_cmd(m, i))
			return (1);
		if (m->job_size > 1 || !is_parent(m))
		{
			if (!m->cmd[i++].args)
				continue ;
			m->cmd[--i].pid = fork();
			if (m->cmd[i].pid == -1)
				return (1);
			if (m->cmd[i].pid == 0)
				child_processes(m, i);
			if (i != m->job_size - 1)
				close(m->cmd[i].pipe[1]);
		}
		else
			parent_process(m);
	}
	return (0);
}
