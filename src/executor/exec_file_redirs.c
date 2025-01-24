/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/24 15:12:19 by smoore           ###   ########.fr       */
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
bool	file_redirections(t_data *data, t_cmd *cmd)
{
	t_cmd *tmp;
	
	tmp = cmd;
	if (!cmd->ins && !cmd->outs)
		return (true);
	while (tmp)
	{
		outfile_redirections(data, tmp->outs);
		infile_redirections(data, tmp->ins);
		tmp = tmp->next;
	}
	return (true);
}
