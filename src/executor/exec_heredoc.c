/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/27 21:59:30 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Write the heredoc to the file descriptor
*
* @param buffer The buffer to write
* @param heredoc The file descriptor
// TODO: Double quotes & restore tabs and spaces
static void	write_heredoc(char *buffer, t_data *data, t_in *in)
{
	char	**split;
	int		i;
	char	*subquote;

	split = command_line_split(buffer, data);
	i = 0;
	subquote = NULL;
	while (split[i])
	{
		if (subquote)
		{
			ft_putstr_fd(subquote, in->heredoc_fd);
			free(subquote);
		}
		else
			ft_putstr_fd(split[i], in->heredoc_fd);
		ft_putchar_fd(' ', in->heredoc_fd);
		i++;
	}
	ft_putstr_fd("\n", in->heredoc_fd);
	free(buffer);
}
*/

/*
* @brief prompt the heredoc to the terminal
*
* @param heredoc The file descriptor
* @param current_job The current command
static void	prompt_heredoc(t_data *data, t_in *in)
{
	char	*buffer;

	ft_putstr_fd(HEREDOC_PROMPT, STDOUT_FILENO);
	buffer = get_next_line(0);
	while (buffer)
	{
		if (ft_strncmp(buffer, in->eof, in->eof_len) == 0)
		{
			free(buffer);
			break ;
		}
		write_heredoc(ft_strtrim(buffer, "\n"), data, in);
		free(buffer);
		ft_putstr_fd(HEREDOC_PROMPT, STDOUT_FILENO);
		buffer = get_next_line(0);
	}
}
*/

/*
* @brief Direct the heredoc to the file descriptor
*
* @param data The data struct
* @param cmd The current command
int	direct_heredoc(t_data *data, t_in *in, int *heredoc_count)
{
	char	filename[256];

	if (!in->eof)
		return (-1);
	else if (in->eof)
	{
		ft_bzero(filename, 256);
		ft_snprintf(filename, sizeof(filename), "/tmp/hd2sh9fd8F32_%d",
			*heredoc_count);
		in->heredoc_fd = open(filename,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (in->heredoc_fd == -1)
			handle_error_parent(data, NULL, 0, true);
		prompt_heredoc(data, in);
		heredoc_count++;
		close(in->heredoc_fd);
//		in->heredoc_fd = open(filename, O_RDONLY, 0644);
		return (in->heredoc_fd);
	}
	return (-1);
}
*/
