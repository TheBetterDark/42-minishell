/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 17:26:06 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

static void	handle_sig_exit(int *status)
{
	if (WTERMSIG(*status) != SIGPIPE)
		*status = WTERMSIG(*status) + 128;
	else
		*status = 0;
}

void	wait_for_status(t_mini *m, int *status)
{
	int	i;

	i = 0;
	while (i < m->job_size)
	{
		if (m->cmd[i].args)
			wait(status);
		else
		{
			*status = 0;
			break ;
		}
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status))
			handle_sig_exit(status);
		if (*status == 130 && m->is_print_sig)
			printf("^C\n");
		else if (*status == 131 && m->is_print_sig)
			printf("^\\Quit: 3\n");
		if (*status == 130 || *status == 131)
			m->is_print_sig = 0;
		i++;
	}
}

bool	executor(t_mini *m)
{
	int	status;
	int	i;

	if (is_heredoc(m))
		return (1);
	cmd_redir(m);
	if (is_command(m))
		return (1);
	i = 0;
	while (i < m->job_size - 1)
	{
		close(m->cmd[i].pipe[0]);
		close(m->cmd[i++].pipe[1]);
	}
	if (!is_parent(m) || m->job_size != 1)
	{
		wait_for_status(m, &status);
		m->exit_status = status;
	}
	return (0);
}
