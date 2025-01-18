/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/18 20:51:21 by smoore           ###   ########.fr       */
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
		handle_error_parent(data, NULL, EXIT_FAILURE, true);
		close(data->r_input_fd);
	}
	if (data->r_output_fd != -1
		&& dup2(data->r_output_fd, STDOUT_FILENO) == -1)
	{
		handle_error_parent(data, NULL, EXIT_FAILURE, true);
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

static void	execute_child_process(t_data *data, t_cmd *cmd)
{
	signal(SIGINT, SIG_IGN);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		signal(SIGINT, handle_sigint_child);
		if (!file_redirections(data, cmd))
			return ;
		redirect_child_stdio(data, &cmd->i, data->pipe_ct);
		close_pipes(data, data->pipe_ct);
		if (data->r_input_fd != -1
			&& dup2(data->r_input_fd, STDIN_FILENO) == -1)
			handle_error_child(data, NULL, EXIT_FAILURE, true);
		if (data->r_output_fd != -1
			&& dup2(data->r_output_fd, STDOUT_FILENO) == -1)
			handle_error_child(data, NULL, EXIT_FAILURE, true);
		if (check_for_builtins(data, cmd))
			exit(data->exit_stat);
		if (execve(cmd->cmdv[0], cmd->cmdv, data->env))
			return (handle_error_child(data, "", 127, true));
	}
	else if (cmd->pid < 0)
		return (handle_error_parent(data, NULL, EXIT_FAILURE, true));
}

/*
* @brief Execute the commands
*
* @param data The data struct
*/
static void	execute_commands(t_data *data)
{
	t_cmd	*current_cmd;

	if (data->job->next == NULL && is_builtin_command(data->job->cmdv[0]))
		return (execute_parent_process(data)); // needs a get_heredocs
	if (data->pipe_ct)
		init_pipes(data, data->pipe_ct);
//	direct_heredoc(data, data->job);
	current_cmd = data->job;
	while (current_cmd)
	{
		get_heredocs(data, current_cmd);
		execute_child_process(data, current_cmd);
		current_cmd = current_cmd->next;
	}
	current_cmd = data->job;
	close_pipes(data, data->pipe_ct);
	while (current_cmd)
	{
		if (current_cmd->pid != 0)
		{
			waitpid(current_cmd->pid, &data->exit_stat, 0);
			handle_command_not_found(data, current_cmd->cmdv[0]);
			data->exit_stat = WEXITSTATUS(data->exit_stat);
		}
		unlink(current_cmd->input_fn);
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
		return (handle_error_parent(data, NULL, EXIT_FAILURE, true));
	data->save_stdout = dup(STDOUT_FILENO);
	if (data->save_stdout == -1)
		return (close(data->save_stdin),
			handle_error_parent(data, NULL, EXIT_FAILURE, true));
	execute_commands(data);
	if (dup2(data->save_stdout, STDOUT_FILENO) == -1)
		return (close(data->save_stdin), close(data->save_stdout),
			handle_error_parent(data, NULL, EXIT_FAILURE, true));
	close(data->save_stdout);
	if (dup2(data->save_stdin, STDIN_FILENO) == -1)
		return (close(data->save_stdin),
			handle_error_parent(data, NULL, EXIT_FAILURE, true));
	close(data->save_stdin);
}
