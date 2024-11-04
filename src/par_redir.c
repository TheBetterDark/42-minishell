/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

static void	get_size(t_mini *m, int idx, t_token *now)
{
	int		ct;
	t_token	*tmp;

	tmp = now;
	ct = 0;
	while (now)
	{
		if (now->type == PIPE)
			break ;
		if (now->type >= 1 && now->type <= 3)
			ct++;
		now = now->next;
	}
	m->cmd[idx].rdr_ct = ct;
	ct = 0;
	now = tmp;
	while (now)
	{
		if (now->type == PIPE)
			break ;
		if (now->type == HEREDOC)
			ct++;
		now = now->next;
	}
	m->cmd[idx].hdc_size = ct;
}

static void	assign_heredoc(t_mini *m, int idx, t_token *cur)
{
	int	i;

	i = 0;
	while (i < m->cmd[idx].hdc_size)
	{
		if (cur->type == FD)
		{
			if (cur->next->type == HEREDOC)
			{
				m->cmd[idx].hdc[i].fd = ft_atoi(cur->cont);
				cur = cur->next->next;
				m->cmd[idx].hdc[i++].eof = cur->cont;
				i++;
			}
		}
		else if (cur->type == HEREDOC)
		{
			m->cmd[idx].hdc[i].fd = 0;
			cur = cur->next;
			m->cmd[idx].hdc[i++].eof = cur->cont;
		}
		cur = cur->next;
	}
}

static void	assign_redir(t_mini *m, int idx, t_token *cur)
{
	int	i;

	i = 0;
	while (i < m->cmd[idx].rdr_ct)
	{
		if (cur->type == FD)
		{
			if (cur->next->type != HEREDOC)
			{
				set_custom_fds(&(m->cmd[idx]), i++, cur, cur->next->next);
				cur = cur->next->next;
			}
		}
		else if (cur->type >= 1 && cur->type <= 3)
		{
			set_default_fds(&(m->cmd[idx]), i++, cur, cur->next);
			cur = cur->next;
		}
		cur = cur->next;
	}
}

bool	parse_redirect_and_heredoc(t_mini *m)
{
	int		i;
	t_token	*current;

	current = m->t_head->next;
	i = 0;
	while (i < m->job_size && current)
	{
		get_size(m, i, current);
		if (rdr_malloc(m, i))
			return (1);
		assign_redir(m, i, current);
		assign_heredoc(m, i, current);
		i++;
		current = find_cmd_after_pipe(current);
	}
	return (0);
}
