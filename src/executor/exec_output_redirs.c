/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_output_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/21 21:41:27 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	check_for_open_redirect(t_data *d, t_cmd *cur)
{
	if (cur->open_fn)
	{
		d->r_output_fd = open(cur->open_fn, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (d->r_output_fd == -1)
		{
			perror("dup2 open");
			exit(EXIT_FAILURE);
		}
		if (dup2(d->r_output_fd, 1) == -1)
		{
			perror("dup2 open");
			exit(EXIT_FAILURE);
		}
		close(d->r_output_fd);
	}
}

void	check_for_append_redirect(t_data *d, t_cmd *cur)
{
	if (cur->append_fn)
	{
		d->r_output_fd = open(cur->append_fn, O_CREAT | O_RDWR | O_APPEND,
				0644);
		if (d->r_output_fd == -1)
		{
			perror("dup2 open");
			exit(EXIT_FAILURE);
		}
		if (dup2(d->r_output_fd, 1) == -1)
		{
			perror("dup2 open");
			exit(EXIT_FAILURE);
		}
		close(d->r_output_fd);
	}
}
