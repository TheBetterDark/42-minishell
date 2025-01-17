/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/17 14:43:25 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Write the heredoc to the file descriptor
*
* @param buffer The buffer to write
* @param heredoc The file descriptor
*/
// TODO: Double quotes & restore tabs and spaces
static void	write_heredoc(char *buffer, t_data *data)
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
			ft_putstr_fd(subquote, data->r_input_fd);
			free(subquote);
		}
		else
			ft_putstr_fd(split[i], data->r_input_fd);
		ft_putchar_fd(' ', data->r_input_fd);
		i++;
	}
	ft_putstr_fd("\n", data->r_input_fd);
	free(buffer);
}

/*
* @brief prompt the heredoc to the terminal
*
* @param heredoc The file descriptor
* @param current_job The current command
*/
static void	prompt_heredoc(t_data *data, t_cmd *cmd)
{
	char	*buffer;

	ft_putstr_fd(HEREDOC_PROMPT, STDOUT_FILENO);
	buffer = get_next_line(0);
	while (buffer)
	{
		if (ft_strncmp(buffer, cmd->eof, cmd->e_len) == 0)
		{
			free(buffer);
			break ;
		}
		write_heredoc(ft_strtrim(buffer, "\n"), data);
		free(buffer);
		ft_putstr_fd(HEREDOC_PROMPT, STDOUT_FILENO);
		buffer = get_next_line(0);
	}
}

/*
* @brief Direct the heredoc to the file descriptor
*
* @param data The data struct
* @param cmd The current command
*/
void	direct_heredoc(t_data *data, t_cmd *cmd)
{
	int		heredoc_count;
	char	filename[256];

	heredoc_count = 0;
	while (cmd)
	{
		if (cmd->eof)
		{
			ft_snprintf(filename, sizeof(filename), "hd2sh9fd8F32_%d",
				heredoc_count);
			data->r_input_fd = open(filename,
					O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->r_input_fd == -1)
				handle_error_parent(data, NULL, 0, true);
			prompt_heredoc(data, cmd);
			cmd->input_fn = ft_strdup(filename);
			close(data->r_input_fd);
			data->r_input_fd = -1;
		}
		heredoc_count++;
		cmd = cmd->next;
	}
}
