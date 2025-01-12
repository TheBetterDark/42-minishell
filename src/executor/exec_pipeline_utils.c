/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 10:09:34 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	direct_pipe_input(void)
{
	unlink("hd2sh9fd8F32");
}

void	safe_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(old_fd);
}

void	redirect_child_fds(int input_fd, int output_fd)
{
	safe_dup2(input_fd, STDIN_FILENO);
	safe_dup2(output_fd, STDOUT_FILENO);
}
