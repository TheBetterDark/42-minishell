/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/22 18:56:21 by smoore           ###   ########.fr       */
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
	if (cmd->outs->truc_fn)
	{
		data->r_output_fd = open(cmd->outs->truc_fn,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->r_output_fd == -1)
			handle_error_parent(data, NULL, EXIT_FAILURE, true);
		if (dup2(data->r_output_fd, 1) == -1)
			handle_error_parent(data, NULL, EXIT_FAILURE, true);
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
	if (cmd->outs->append_fn) // needs to open all cmd->outs and only redirect the last one
	{
		data->r_output_fd = open(cmd->outs->append_fn,
				O_CREAT | O_RDWR | O_APPEND, 0644);
		if (data->r_output_fd == -1)
			handle_error_parent(data, NULL, EXIT_FAILURE, true);
		if (dup2(data->r_output_fd, 1) == -1)
			handle_error_parent(data, NULL, EXIT_FAILURE, true);
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
	t_cmd *tmp;
	
	tmp = cmd;
	while (tmp)
	{
		check_for_open_redirect(data, cmd);
		check_for_append_redirect(data, cmd);
		if (cmd->ins->read_fn)
		{
			data->r_input_fd = open(cmd->ins->read_fn, O_RDONLY, 0644);
			if (data->r_input_fd == -1)
				return (handle_error_parent(data, NULL, EXIT_FAILURE, true), false);
			if (dup2(data->r_input_fd, STDIN_FILENO) == -1)
				handle_error_parent(data, NULL, EXIT_FAILURE, true);
		}
	}
	return (true);
}
