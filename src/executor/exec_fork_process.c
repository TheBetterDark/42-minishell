/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/09 19:02:14 by smoore           ###   ########.fr       */
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

void	redirect_child_fds(t_data *d, t_cmd *cur)
{
	if (d->prev_pipefd[0] != -1)
	{
		if (dup2(d->prev_pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 d->prev_pipefd[0]");
			exit(EXIT_FAILURE);
		}
		close(d->prev_pipefd[0]);
	}
	if (cur->next)
	{
		if (dup2(cur->pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 cur->pipefd[1]");
			exit(EXIT_FAILURE);
		}
		close(cur->pipefd[1]);
	}
}

void	execute_parent_process(t_data *d, t_cmd *cur)
{
	redirect_child_fds(d, cur);
	check_for_builtins(d, cur);
}

void	fork_child_process(t_data *d, t_cmd *cur)
{
	cur->pid = fork();
	signal(SIGINT, SIG_IGN);
	if (cur->pid == 0)
	{
		signal(SIGINT, handle_sigint);
		redirect_child_fds(d, cur);
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
