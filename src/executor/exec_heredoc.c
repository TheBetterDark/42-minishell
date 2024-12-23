/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/23 18:14:44 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

// TODO: Change to use readline & handle signals
void	write_heredoc(int heredoc, t_cmd *cur)
{
	char	*buf;

	buf = readline("> ");
	while (buf)
	{
		if (ft_strncmp(buf, cur->eof, cur->e_len) == 0)
		{
			free(buf);
			break ;
		}
		ft_putstr_fd(buf, heredoc);
		ft_putchar_fd('\n', heredoc);
		free(buf);
		buf = readline("> ");
	}
}

void	direct_heredoc(t_data *d, t_cmd *cur)
{
	if (cur->eof)
	{
		d->r_input_fd = open("hd2sh9fd8F32", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (d->r_input_fd == -1)
		{
			perror("heredoc open");
			exit(EXIT_FAILURE);
		}
		write_heredoc(d->r_input_fd, cur);
		cur->input_fn = ft_strdup("hd2sh9fd8F32");
		close(d->r_input_fd);
		d->r_input_fd = -1;
	}
}
