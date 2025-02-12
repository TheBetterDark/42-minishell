/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_file_descriptors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:38:59 by smoore            #+#    #+#             */
/*   Updated: 2025/02/11 15:45:38 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	open_read_files(t_ins *ins, t_data *data);
void	open_write_files(t_outs *outs, t_data *data);
void	open_files(t_cmd *cmd, t_data *data);
void	prepare_file_descriptors(t_data *data, t_cmd *cur);

void	open_read_files(t_ins *ins, t_data *data)
{
	t_ins	*ptr;

	if (!ins)
		return ;
	ptr = ins;
	while (ptr)
	{
		if (ptr->read_fn)
			data->read_fd = open(ptr->read_fn, O_RDONLY, 0644);
		ptr = ptr->next;
	}
	if (data->read_fd == -1)
		return ;
	if (dup2(data->read_fd, STDIN_FILENO) == -1)
		return ;
}

void	open_write_files(t_outs *outs, t_data *data)
{
	t_outs	*ptr;

	if (!outs)
		return ;
	ptr = outs;
	while (ptr)
	{
		if (ptr->trunc_fn)
			data->write_fd = open(ptr->trunc_fn, O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		else if (ptr->append_fn)
			data->write_fd = open(ptr->append_fn, O_CREAT | O_WRONLY | O_APPEND,
					0644);
		ptr = ptr->next;
	}
	if (data->write_fd == -1)
		return ;
	if (dup2(data->write_fd, STDOUT_FILENO) == -1)
		return ;
}

void	open_files(t_cmd *cmds, t_data *data)
{
	if (!cmds->ins && !cmds->outs)
		return ;
	open_read_files(cmds->ins, data);
	open_write_files(cmds->outs, data);
}

void	prepare_file_descriptors(t_data *data, t_cmd *cur)
{
	if (cur->ins || cur->outs)
	{
		open_files(cur, data);
		if (data->read_fd != -1 && (dup2(data->read_fd, STDIN_FILENO) == -1))
		{
			close(data->read_fd);
			return ;
		}
		if (data->write_fd != -1 && (dup2(data->write_fd, STDOUT_FILENO) == -1))
		{
			close(data->write_fd);
			return ;
		}
	}
}
