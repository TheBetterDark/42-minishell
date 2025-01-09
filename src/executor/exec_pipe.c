/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/09 19:08:13 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	create_child_pipe(t_cmd *cur)
{
	if (pipe(cur->pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	close_pipe_ends(t_data *d)
{
	if (d->input_fd != STDIN_FILENO)
		close(d->input_fd);
	if (d->output_fd != STDOUT_FILENO)
		close(d->output_fd);
}

void	direct_pipe_input(t_data *d, t_cmd *cur)
{
	close_pipe_ends(d);
	d->input_fd = cur->pipefd[0];
	unlink("hd2sh9fd8F32");
}
