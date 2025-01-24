/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_infile_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/24 14:06:56 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief File redirections
*
* @param data The data struct
* @param cmd The current command
*
* @return True if the redirections are successful, false otherwise
*/
bool	infile_redirections(t_data *data, t_cmd *cmd)
{
	t_in	*tmp;

	if (!cmd->ins)
		return (false);
	tmp = cmd->ins;
	while (tmp)
	{
		if (cmd->ins->read_fn)
			data->r_input_fd = open(cmd->ins->read_fn, O_RDONLY, 0644);
		tmp = tmp->next;
	}
	if (data->r_input_fd == -1)
		return (handle_error_parent(data, NULL, EXIT_FAILURE, true), false);
	if (dup2(data->r_input_fd, STDIN_FILENO) == -1)
		handle_error_parent(data, NULL, EXIT_FAILURE, true);
	return (true);
}
