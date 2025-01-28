/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_infile_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/28 11:31:25 by smoore           ###   ########.fr       */
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
bool	infile_redirections(t_data *data, t_in *in)
{
	t_in	*tmp;

	if (!in)
		return (false);
	tmp = in;
	while (tmp)
	{
		if (tmp->read_fn)
			data->r_input_fd = open(tmp->read_fn, O_RDONLY, 0644);
		tmp = tmp->next;
	}
	if (data->r_input_fd == -1)
		return (handle_error_parent(data, NULL, EXIT_FAILURE, true), false);
	if (dup2(data->r_input_fd, STDIN_FILENO) == -1)
		handle_error_parent(data, NULL, EXIT_FAILURE, true);
	return (true);
}
