/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 10:39:33 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	create_cmd_pipe(t_cmd *cur)
{
	if (pipe(cur->pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	close_pipe_ends(t_cmd *job)
{
	t_cmd	*cur;

	cur = job;
	while (cur)
	{
		if (cur->pipefd[0] != -1)
			close(cur->pipefd[0]);
		if (cur->pipefd[1] != -1)
			close(cur->pipefd[1]);
		cur = cur->next;
	}
}

void	connect_pipeline(t_cmd *cur)
{
	t_cmd	*tmp;

	tmp = cur;
	while (tmp)
	{
		if (cur->next)
		{
			cur->output_fd = cur->pipefd[1];
			cur->next->output_fd = cur->pipefd[0];
		}
		else
			cur->output_fd = STDOUT_FILENO;
		if (cur->input_fd == -1)
			cur->input_fd = STDIN_FILENO;
		tmp = tmp->next;
	}
}
