/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/15 17:13:56 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Execute the parent process
*
* @param data The data struct
*/
static void	execute_parent_process(t_data *data)
{
	if (!file_redirections(data, data->job))
		return ;
	if (data->r_input_fd != -1
		&& dup2(data->r_input_fd, STDIN_FILENO) == -1)
	{
		handle_error(data, NULL, EXIT_FAILURE, true);
		close(data->r_input_fd);
	}
	if (data->r_output_fd != -1
		&& dup2(data->r_output_fd, STDOUT_FILENO) == -1)
	{
		handle_error(data, NULL, EXIT_FAILURE, true);
		close(data->r_output_fd);
	}
	check_for_builtins(data, data->job);
}

/*
* @brief Execute the child process
*
* @param data The data struct
* @param cmd The current command
*/

static void	execute_child_process(t_data *data, t_cmd *cmd, int **pipe_fds)
{
	signal(SIGINT, SIG_IGN);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		signal(SIGINT, handle_sigint_child);
		if (!file_redirections(data, cmd))
			return ;
		redirect_child_stdio(pipe_fds, &cmd->i, data->cmd_ct);
		close_pipes(pipe_fds, data->cmd_ct);
		if (data->r_input_fd != -1
			&& dup2(data->r_input_fd, STDIN_FILENO) == -1)
			handle_error(data, NULL, EXIT_FAILURE, false);
		if (data->r_output_fd != -1
			&& dup2(data->r_output_fd, STDOUT_FILENO) == -1)
			handle_error(data, NULL, EXIT_FAILURE, false);
		if (check_for_builtins(data, cmd))
			exit(data->exit_stat);
		if (execve(cmd->cmdv[0], cmd->cmdv, data->env))
			return (handle_error(data, ERR_CMD_NOT_FOUND, EXIT_FAILURE, false));
	}
	else if (cmd->pid < 0)
		return (handle_error(data, NULL, EXIT_FAILURE, true));
	if (cmd->eof)
		wait(NULL);
}

/*
* @brief Execute the commands
*
* @param data The data struct
*/
static void	execute_commands(t_data *data)
{
	t_cmd	*current_cmd;
	int		**pipe_fds;

	if (data->job->next == NULL && is_builtin_command(data->job->cmdv[0]))
		return (execute_parent_process(data));
	current_cmd = data->job;
	pipe_fds = NULL;
	init_pipes(&pipe_fds, data->cmd_ct);
	while (current_cmd)
	{
		execute_child_process(data, current_cmd, pipe_fds);
		unlink("hd2sh9fd8F32");
		current_cmd = current_cmd->next;
	}
	current_cmd = data->job;
	close_pipes(pipe_fds, data->cmd_ct);
	while (current_cmd)
	{
		if (current_cmd->pid != 0)
		{
			waitpid(current_cmd->pid, &data->exit_stat, 0);
			data->exit_stat = WEXITSTATUS(data->exit_stat);
		}
		current_cmd = current_cmd->next;
	}
}

/*
* @brief Execute the commands
*
* @param data The data struct
*/
void	executor(t_data *data)
{
	if (!data->job)
		return ;
	data->save_stdin = dup(STDIN_FILENO);
	if (data->save_stdin == -1)
		return (handle_error(data, NULL, EXIT_FAILURE, true));
	data->save_stdout = dup(STDOUT_FILENO);
	if (data->save_stdout == -1)
		return (close(data->save_stdin),
			handle_error(data, NULL, EXIT_FAILURE, true));
	execute_commands(data);
	if (dup2(data->save_stdout, STDOUT_FILENO) == -1)
		return (close(data->save_stdin), close(data->save_stdout),
			handle_error(data, NULL, EXIT_FAILURE, true));
	close(data->save_stdout);
	if (dup2(data->save_stdin, STDIN_FILENO) == -1)
		return (close(data->save_stdin),
			handle_error(data, NULL, EXIT_FAILURE, true));
	close(data->save_stdin);
}
