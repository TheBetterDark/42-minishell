/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

t_token	*find_cmd_after_pipe(t_token *current)
{
	while (current)
	{
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	if (current)
		return (current->next);
	else
		return (NULL);
}

bool	rdr_malloc(t_mini *m, int idx)
{
	if (m->cmd[idx].rdr_ct != 0)
	{
		m->cmd[idx].rdr = ft_malloc(m->cmd[idx].rdr_ct * sizeof(t_rdr),
				m->mem);
		if (!m->cmd[idx].rdr)
			return (1);
	}
	if (m->cmd[idx].hdc_size != 0)
	{
		m->cmd[idx].hdc = ft_malloc(m->cmd[idx].hdc_size * sizeof(t_hdc),
				m->mem);
		if (!m->cmd[idx].hdc)
			return (1);
	}
	return (0);
}

void	set_default_fds(t_cmd *cmd, int idx, t_token *type, t_token *fn)
{
	if (type->type == APPEND || type->type == REDIR_OUT)
		cmd->rdr[idx].fd = 1;
	if (type->type == REDIR_IN)
		cmd->rdr[idx].fd = 0;
	cmd->rdr[idx].type = type->type;
	cmd->rdr[idx].fn = fn->cont;
}

void	set_custom_fds(t_cmd *cmd, int idx, t_token *fd, t_token *fn)
{
	cmd->rdr[idx].fd = ft_atoi(fd->cont);
	cmd->rdr[idx].type = fd->next->type;
	cmd->rdr[idx].fn = fn->cont;
}
