/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 10:10:32 by muabdi           ###   ########.fr       */
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

void	execute_parent_process(t_data *d, t_cmd *cur)
{
	redirect_child_fds(cur->input_fd, cur->output_fd);
	check_for_builtins(d, cur);
}

void	fork_child_process(t_data *d, t_cmd *cur)
{
	cur->pid = fork();
	signal(SIGINT, SIG_IGN);
	if (cur->pid == 0)
	{
		signal(SIGINT, handle_sigint);
		redirect_child_fds(cur->input_fd, cur->output_fd);
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
