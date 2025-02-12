/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:38:50 by smoore            #+#    #+#             */
/*   Updated: 2025/02/12 18:51:54 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	parent_waits_for_child(t_data *data, t_cmd *cur);
void	execve_child(t_data *data, t_cmd *cur);
void	prepare_pipeline(t_data *data, t_cmd *cmds);
void	select_process(t_data *data);
void	execute(t_data *data);

void	parent_waits_for_child(t_data *data, t_cmd *cur)
{
	int	status;

	status = 0;
	modify_sigint(IGNORE_SIGNAL, data);
	modify_sigquit(PARENT_SIGNAL);
	waitpid(cur->pid, &status, 0);
	data->exit_stat = WEXITSTATUS(status);
	if (data->exit_stat == 127 && !is_builtin_cmd_child(data->cmds->cmdv[0]))
	{
		if (ft_strchr(cur->cmdv[0], '/'))
			ft_putstr_fd(ft_strrchr(cur->cmdv[0], '/') + 1, 1);
		else
			ft_putstr_fd(cur->cmdv[0], 1);
		ft_putstr_fd(": command not found\n", 1);
	}
}

void	execve_child(t_data *data, t_cmd *cur)
{
	cur->pid = fork();
	if (cur->pid == 0)
	{
		modify_sigint(CHILD_SIGNAL, data);
		modify_sigquit(CHILD_SIGNAL);
		redirect_pipes(data, cur->i);
		prepare_file_descriptors(data, cur);
		close_pipes(data, data->pipe_ct);
		if (cur->cmdv[0])
		{
			if (is_builtin_cmd_child(cur->cmdv[0]))
			{
				execute_builtin(data, cur->cmdv[0]);
				cleanup_child(data, data->exit_stat);
			}
			else if ((execve(cur->cmdv[0], cur->cmdv, data->env)) == -1)
				cleanup_child(data, 127);
		}
		else
		{
			cleanup_child(data, 0);
			exit(EXIT_SUCCESS);
		}
	}
}

void	prepare_pipeline(t_data *data, t_cmd *cmds)
{
	t_cmd	*cur;

	if (data->pipe_ct)
		init_pipes(data, data->pipe_ct);
	cur = cmds;
	while (cur)
	{
		execve_child(data, cur);
		cur = cur->next;
	}
	if (data->pipe_ct)
		close_pipes(data, data->pipe_ct);
	cur = cmds;
	while (cur)
	{
		parent_waits_for_child(data, cur);
		cur = cur->next;
	}
}

void	select_process(t_data *data)
{
	if (!data->cmds->next && is_builtin_cmd_parent(data->cmds->cmdv[0]))
	{
		prepare_file_descriptors(data, data->cmds);
		execute_builtin(data, data->cmds->cmdv[0]);
	}
	else
		prepare_pipeline(data, data->cmds);
}

void	execute(t_data *data)
{
	if (!data->cmds || g_signal != NO_SIGNAL)
		return ;
	data->saved_stdin = dup(STDIN_FILENO);
	if (data->saved_stdin == -1)
		return ;
	close(data->saved_stdin);
	data->saved_stdout = dup(STDOUT_FILENO);
	if (data->saved_stdout == -1)
		return ;
	close(data->saved_stdout);
	select_process(data);
	if (dup2(data->saved_stdin, STDIN_FILENO) == -1)
		return ;
	if (dup2(data->saved_stdout, STDOUT_FILENO) == -1)
		return ;
}
