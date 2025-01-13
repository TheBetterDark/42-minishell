/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/13 11:02:08 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Create a pipe
*
* @param cmd The current job
*/
void	create_cmd_pipe(t_cmd *cmd)
{
	if (pipe(cmd->pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

/*
* @brief Close the pipe ends
*
* @param job List of commands
*/
void	close_pipe_ends(t_cmd *cmds)
{
	t_cmd	*current_cmd;

	current_cmd = cmds;
	while (current_cmd)
	{
		if (current_cmd->pipefd[0] != -1)
		{
			close(current_cmd->pipefd[0]);
			current_cmd->pipefd[0] = -1;
		}
		if (current_cmd->pipefd[1] != -1)
		{
			close(current_cmd->pipefd[1]);
			current_cmd->pipefd[1] = -1;
		}
		current_cmd = current_cmd->next;
	}
}

/*
* @brief Connect the pipeline
*
* @param cmd The current job
*/
void	connect_pipeline(t_cmd *cmd)
{
	t_cmd	*current_cmd;

	current_cmd = cmd;
	while (current_cmd)
	{
		if (cmd->next)
		{
			cmd->output_fd = cmd->pipefd[1];
			cmd->next->input_fd = cmd->pipefd[0];
		}
		else
			cmd->output_fd = STDOUT_FILENO;
		if (cmd->input_fd == -1)
			cmd->input_fd = STDIN_FILENO;
		current_cmd = current_cmd->next;
	}
}
