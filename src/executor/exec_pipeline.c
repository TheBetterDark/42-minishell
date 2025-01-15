/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/15 14:27:10 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"
#include <errno.h>

/*
* @brief Create a pipe
*
* @param cmd The current job
*/
void	init_pipes(int ***pipe_fds, int cmd_ct)
{
	int	i;

	*pipe_fds = malloc(sizeof(int *) * cmd_ct);
	i = 0;
	while (i < cmd_ct - 1)
	{
		(*pipe_fds)[i] = malloc(sizeof(int) * 2);
		if (pipe(*pipe_fds[i]) == -1)
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

void	close_pipes(int **pipe_fds, int cmd_ct)
{
	int	i;

	i = 0;
	while (i < cmd_ct - 1)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		free(pipe_fds[i]);
		i++;
	}
	free(pipe_fds);
}

void	redirect_child_stdio(int **pipe_fds, int *i, int cmd_ct)
{
	if (*i > 0)
		dup2(pipe_fds[*i - 1][0], STDIN_FILENO);
	if (*i < cmd_ct - 1)
		dup2(pipe_fds[*i][1], STDOUT_FILENO);
}
