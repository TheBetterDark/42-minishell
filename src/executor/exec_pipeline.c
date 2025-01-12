/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 19:27:27 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Create a pipe
*
* @param current_cmd The current job
*/
void	create_cmd_pipe(t_cmd *current_cmd)
{
	if (pipe(current_cmd->pipefd) == -1)
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
* @param current_cmd The current job
*/
void	connect_pipeline(t_cmd *current_cmd)
{
	t_cmd	*tmp;

	tmp = current_cmd;
	while (tmp)
	{
		if (current_cmd->next)
		{
			current_cmd->output_fd = current_cmd->pipefd[1];
			current_cmd->next->input_fd = current_cmd->pipefd[0];
		}
		else
			current_cmd->output_fd = STDOUT_FILENO;
		if (current_cmd->input_fd == -1)
			current_cmd->input_fd = STDIN_FILENO;
		tmp = tmp->next;
	}
}
