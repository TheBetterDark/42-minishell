/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/14 20:06:56 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"
#include <errno.h>

/*
* @brief Create a pipe
*
* @param cmd The current job
*/
void	init_pipes(int pipe_fds[][2], int cmd_ct)
{
	int	i;

	i = 0;
	while (i < cmd_ct - 1)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

/*
* @brief Close the pipe ends
*
* @param job List of commands
*/

void	close_pipes(int pipe_fds[][2], int cmd_ct)
{
	int	i;

	i = 0;
	while (i < cmd_ct - 1)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}

void	redirect_child_stdio(int pipe_fds[][2], int *i, int cmd_ct)
{
	if (*i > 0)
		dup2(pipe_fds[*i - 1][0], STDIN_FILENO);
	if (*i < cmd_ct - 1)
		dup2(pipe_fds[*i][1], STDOUT_FILENO);
}
