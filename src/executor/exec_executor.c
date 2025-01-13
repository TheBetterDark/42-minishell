/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/13 13:18:18 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Restore the file descriptors
*
* @param save_stdout The saved stdout file descriptor
* @param save_stdin The saved stdin file descriptor
*/
static void	restore_file_descriptors(int save_stdout, int save_stdin)
{
	if (dup2(save_stdout, 1) == -1)
	{
		perror("dup2 save_stdout");
		exit(EXIT_FAILURE);
	}
	close(save_stdout);
	if (dup2(save_stdin, 0) == -1)
	{
		perror("dup2 save_stdin");
		exit(EXIT_FAILURE);
	}
	close(save_stdin);
}

/*
* @brief Execute the parent process
*
* @param data The data struct
*/
static void	execute_parent_process(t_data *data)
{
	if (!file_redirections(data, data->job))
		return ;
	if (dup2(data->job->input_fd, STDIN_FILENO) == -1)
		handle_error(data, NULL, EXIT_FAILURE, true);
	if (dup2(data->job->output_fd, STDOUT_FILENO) == -1)
		handle_error(data, NULL, EXIT_FAILURE, true);
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
	if (!file_redirections(data, cmd))
		return ;
	signal(SIGINT, SIG_IGN);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		signal(SIGINT, handle_sigint);
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
			handle_error(data, NULL, EXIT_FAILURE, true);
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
			handle_error(data, NULL, EXIT_FAILURE, true);
		if (check_for_builtins(data, cmd))
			exit(data->exit_stat);
		if (execve(cmd->cmdv[0], cmd->cmdv, data->env))
			return (handle_error(data, NULL, EXIT_FAILURE, true));
		exit_minishell(data, EXIT_FAILURE);
	}
	else if (cmd->pid < 0)
		return (handle_error(data, NULL, EXIT_FAILURE, true));
	unlink("hd2sh9fd8F32");
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
		return (execute_parent_process(data));
	current_cmd = data->job;
	while (current_cmd)
	{
		execute_child_process(data, current_cmd);
		unlink("hd2sh9fd8F32");
		current_cmd = current_cmd->next;
	}
	current_cmd = data->job;
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
	int		save_stdout;
	int		save_stdin;

	if (!data->job)
		return (handle_error(data, ERR_UNKNOWN, EXIT_FAILURE, false));
	save_stdin = dup(0);
	if (!save_stdin)
		return (handle_error(data, NULL, EXIT_FAILURE, true));
	save_stdout = dup(1);
	if (!save_stdout)
		return (handle_error(data, NULL, EXIT_FAILURE, true));
	if (data->job->next)
		connect_pipeline(data->job);
	execute_commands(data);
	restore_file_descriptors(save_stdout, save_stdin);
	close_pipe_ends(data->job);
}
