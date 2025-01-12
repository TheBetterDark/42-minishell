/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 20:57:36 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Write the heredoc to the file descriptor
*
* @param heredoc The file descriptor
* @param current_job The current command
*/
void	write_heredoc(int heredoc, t_cmd *cmd)
{
	char	*buffer;

	ft_printf(HEREDOC_PROMPT);
	buffer = get_next_line(0);
	while (buffer)
	{
		if (ft_strncmp(buffer, cmd->eof, cmd->e_len) == 0)
		{
			free(buffer);
			break ;
		}
		ft_putstr_fd(buffer, heredoc);
		free(buffer);
		ft_printf(HEREDOC_PROMPT);
		buffer = get_next_line(0);
	}
}

/*
* @brief Direct the heredoc to the file descriptor
*
* @param d The data struct
* @param cmd The current command
*/
void	direct_heredoc(t_data *d, t_cmd *cmd)
{
	if (cmd->eof)
	{
		d->r_input_fd = open("hd2sh9fd8F32", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (d->r_input_fd == -1)
		{
			perror("heredoc open");
			exit(EXIT_FAILURE);
		}
		write_heredoc(d->r_input_fd, cmd);
		cmd->input_fn = ft_strdup("hd2sh9fd8F32");
		close(d->r_input_fd);
		d->r_input_fd = -1;
	}
}
