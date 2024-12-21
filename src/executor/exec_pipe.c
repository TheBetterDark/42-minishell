/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/21 21:41:27 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	create_child_pipe(t_data *d)
{
	if (pipe(d->pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	close_pipe_ends(t_data *d)
{
	if (d->input_fd != 0)
		close(d->input_fd);
	if (d->output_fd != 1)
		close(d->output_fd);
}

void	direct_pipe_input(t_data *d)
{
	close_pipe_ends(d);
	d->input_fd = d->pipefd[0];
	unlink("hd2sh9fd8F32");
}
