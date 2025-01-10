/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/10 19:33:03 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	direct_output(t_data *d, t_cmd *cur)
{
	check_for_open_redirect(d, cur);
	check_for_append_redirect(d, cur);
}

void	direct_input(t_data *d, t_cmd *cur)
{
	if (cur->input_fn)
	{
		d->r_input_fd = open(cur->input_fn, O_RDONLY, 0644);
		if (d->r_input_fd == -1)
		{
			perror("input_fd open");
			exit(EXIT_FAILURE);
		}
		safe_dup2(d->r_input_fd, STDIN_FILENO);
	}
}

void	file_redirections(t_data *d, t_cmd *cur)
{
	direct_heredoc(d, cur);
	direct_output(d, cur);
	direct_input(d, cur);
}
