/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/18 20:50:05 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static void	heredoc_sigint(int sig)
{
//	g_signal = signo;
	(void)sig;
	printf("\n");
	exit(EXIT_FAILURE);
}

void	get_heredocs(t_data *data, t_cmd *cur_cmd)
{
	t_ins	*cur;	
	pid_t	pid;
	int		wstatus;
	char	*buf;

	if (!cur_cmd->ins)
		return ;
	cur = cur_cmd->ins;
	while (cur)
	{
		if (cur->eof)
		{
			pipe(cur->pipe_fds);
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, heredoc_sigint);
				ft_putstr_fd("> ", STDOUT_FILENO);
				buf = get_next_line(STDIN_FILENO);
				// expand VARS
				close(cur->pipe_fds[0]);
				ft_putstr_fd(buf, cur->pipe_fds[1]);
				free(buf);
			}
		}
		else
			waitpid(pid, &wstatus, NULL);
		cur = cur->next;
	}
}
