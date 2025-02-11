/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:38:56 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 16:04:22 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	init_pipes(t_data *data, int pipe_ct);
void	close_pipes(t_data *data, int pipe_ct);
void	free_pipes(t_data *data, int pipe_ct);
void	redirect_pipes(t_data *data, int i);

void	init_pipes(t_data *data, int pipe_ct)
{
	int	i;

	i = 0;
	data->pipe_fd = (int **)malloc(sizeof(int *) * pipe_ct);
	while (i < pipe_ct)
	{
		data->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!data->pipe_fd[i])
		{
			perror("pipe malloc");
			exit(EXIT_FAILURE);
		}
		if (pipe(data->pipe_fd[i]) == -1)
		{
			perror("pipe failure");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes(t_data *data, int pipe_ct)
{
	int	i;

	i = 0;
	while (i < pipe_ct)
	{
		close(data->pipe_fd[i][0]);
		close(data->pipe_fd[i][1]);
		i++;
	}
}

void	free_pipes(t_data *data, int pipe_ct)
{
	int	i;

	i = 0;
	if (!data->pipe_fd)
		return ;
	while (i < pipe_ct)
	{
		free(data->pipe_fd[i]);
		i++;
	}
	free(data->pipe_fd);
}

void	redirect_pipes(t_data *data, int i)
{
	if (i > 0)
		dup2(data->pipe_fd[i - 1][0], STDIN_FILENO);
	if (i < data->pipe_ct)
		dup2(data->pipe_fd[i][1], STDOUT_FILENO);
}
