/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

bool	is_parent(t_mini *m)
{
	if (!m->cmd[0].args)
		return (0);
	if (!ft_strncmp(m->cmd[0].args[0], "cd", 3))
		return (1);
	if (!ft_strncmp(m->cmd[0].args[0], "export", 7))
		return (1);
	if (!ft_strncmp(m->cmd[0].args[0], "unset", 6))
		return (1);
	if (!ft_strncmp(m->cmd[0].args[0], "exit", 5))
		return (1);
	return (0);
}

static bool	open_redirect(t_rdr *rdr)
{
	if (rdr->type == REDIR_OUT)
	{
		rdr->o_fd = open(rdr->fn, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (rdr->o_fd == -1)
			return (1);
	}
	else if (rdr->type == APPEND)
	{
		rdr->o_fd = open(rdr->fn, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (rdr->o_fd == -1)
			return (1);
	}
	else if (rdr->type == REDIR_IN)
	{
		rdr->o_fd = open(rdr->fn, O_RDONLY);
		if (rdr->o_fd == -1)
			return (1);
	}
	return (0);
}

void	cmd_redir(t_mini *m)
{
	int	i;
	int	j;

	i = -1;
	while (++i < m->job_size)
	{
		j = -1;
		while (++j < m->cmd[i].rdr_ct)
		{
			if (m->cmd[i].rdr[j].type >= 1 && m->cmd[i].rdr[j].type <= 3)
			{
				if (open_redirect(&(m->cmd[i].rdr[j])))
				{
					ft_putstr_fd("minishell: ", 2);
					perror(m->cmd[i].rdr[j].fn);
					m->exit_status = errno;
					m->cmd[i].rdr[j].if_rdr = 0;
					break ;
				}
				else
					m->cmd[i].rdr[j].if_rdr = 1;
			}
		}
	}
}

bool	create_pipe_for_cmd(t_mini *m, int idx)
{
	if (idx != m->job_size - 1)
	{
		if (pipe(m->cmd[idx].pipe) == -1)
		{
			perror("minishell");
			return (1);
		}
		if (!m->cmd[idx + 1].args)
			close(m->cmd[idx].pipe[0]);
	}
	return (0);
}
