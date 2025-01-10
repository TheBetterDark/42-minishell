
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/10 20:32:40 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	create_cmd_pipe(t_cmd *cur);
void	close_pipe_ends(t_cmd *job);
void	direct_pipe_input(void);
void	safe_dup2(int old_fd, int new_fd);
void	redirect_child_fds(int input_fd, int output_fd);
void	connect_pipeline(t_cmd *cur);

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
	t_cmd *cur;

	cur = job;
	while (cur)
	{
		if (cur->pipefd[0] != -1)
			close(cur->pipefd[0]);
		if (cur->pipefd[1] != -1)
			close(cur->pipefd[1]);
	}
}

void	direct_pipe_input(void)
{
	unlink("hd2sh9fd8F32");
}

void	safe_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(old_fd);
}

void	redirect_child_fds(int input_fd, int output_fd)
{
		safe_dup2(input_fd, STDIN_FILENO);
		safe_dup2(output_fd, STDOUT_FILENO);
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
