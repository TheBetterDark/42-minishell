/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/07 18:47:51 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	execute_child_program(t_data *d, t_cmd *cur)
{
	if (execve(cur->cmdv[0], cur->cmdv, d->env))
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	redirect_child_fds(t_data *d)
{
	if (d->input_fd != 0)
	{
		if (dup2(d->input_fd, 0) == -1)
		{
			perror("dup2 d->input_fd");
			exit(EXIT_FAILURE);
		}
		close(d->input_fd);
	}
	if (d->output_fd != 1)
	{
		if (dup2(d->output_fd, 1) == -1)
		{
			perror("dup2 d->output_fd");
			exit(EXIT_FAILURE);
		}
		close(d->output_fd);
	}
}

void	execute_parent_process(t_data *d, t_cmd *cur)
{
	redirect_child_fds(d);
	check_for_builtins(d, cur);
}

void	fork_child_process(t_data *d, t_cmd *cur)
{
	cur->pid = fork();
	if (cur->pid == 0)
	{
		redirect_child_fds(d);
		if (check_for_builtins(d, cur))
			exit(d->exit_stat);
		execute_child_program(d, cur);
		free_minishell(d);
		free_data(d);
		exit(EXIT_SUCCESS);
	}
	else if (cur->pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
