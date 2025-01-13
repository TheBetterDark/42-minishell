/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/13 13:10:39 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Check for open redirect
*
* @param data The data struct
* @param cmd The current command
*/
static void	check_for_open_redirect(t_data *data, t_cmd *cmd)
{
	if (cmd->open_fn)
	{
		data->r_output_fd = open(cmd->open_fn,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->r_output_fd == -1)
			handle_error(data, NULL, EXIT_FAILURE, true);
		if (dup2(data->r_output_fd, 1) == -1)
			handle_error(data, NULL, EXIT_FAILURE, true);
		close(data->r_output_fd);
	}
}

/*
* @brief Check for append redirect
*
* @param data The data struct
* @param cmd The current command
*/
static void	check_for_append_redirect(t_data *data, t_cmd *cmd)
{
	if (cmd->append_fn)
	{
		data->r_output_fd = open(cmd->append_fn,
				O_CREAT | O_RDWR | O_APPEND, 0644);
		if (data->r_output_fd == -1)
			handle_error(data, NULL, EXIT_FAILURE, true);
		if (dup2(data->r_output_fd, 1) == -1)
			handle_error(data, NULL, EXIT_FAILURE, true);
		close(data->r_output_fd);
	}
}

/*
* @brief File redirections
*
* @param data The data struct
* @param cmd The current command
*
* @return True if the redirections are successful, false otherwise
*/
bool	file_redirections(t_data *data, t_cmd *cmd)
{
	direct_heredoc(data, cmd);
	check_for_open_redirect(data, cmd);
	check_for_append_redirect(data, cmd);
	if (cmd->input_fn)
	{
		data->r_input_fd = open(cmd->input_fn, O_RDONLY, 0644);
		if (data->r_input_fd == -1)
			return (handle_error(data, NULL, EXIT_FAILURE, true), false);
		if (dup2(data->r_input_fd, STDIN_FILENO) == -1)
			handle_error(data, NULL, EXIT_FAILURE, true);
	}
	return (true);
}
