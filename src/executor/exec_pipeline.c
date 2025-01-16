/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/16 19:15:48 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"
#include <errno.h>

/*
* @brief Create a pipe
*
* @param cmd The current job
*/
void	init_pipes(t_data *data, int pipe_ct)
{
	int	i;

	i = 0;
	data->pipe_fds = (int **)malloc(pipe_ct * sizeof(int *));
	while (i < pipe_ct)
	{
		data->pipe_fds[i] = malloc(sizeof(int) * 2);
		if (!data->pipe_fds[i])
		{
			perror("pipe malloc");
			exit(EXIT_FAILURE);
		}
		if (pipe(data->pipe_fds[i]) == -1)
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

void	close_pipes(t_data *data, int pipe_ct)
{
	int	i;

	i = 0;
	while (i < pipe_ct)
	{
		close(data->pipe_fds[i][0]);
		close(data->pipe_fds[i][1]);
		i++;
	}
}

void	free_pipes(t_data *data, int pipe_ct)
{
	int	i;

	i = 0;
	while (i < pipe_ct)
	{
		free(data->pipe_fds[i]);
		i++;
	}
}

void	redirect_child_stdio(t_data *data, int *i, int pipe_ct)
{
	if (*i > 0)
		dup2(data->pipe_fds[*i - 1][0], STDIN_FILENO);
	if (*i < pipe_ct)
		dup2(data->pipe_fds[*i][1], STDOUT_FILENO);
}
