/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

static int	count_pipes(t_mini *m)
{
	int		ct;
	t_token	*current;

	ct = 1;
	current = m->t_head->next;
	while (current)
	{
		if (current->type == PIPE)
			ct++;
		current = current->next;
	}
	return (ct);
}

static bool	init_commands(t_mini *m)
{
	int	i;

	m->job_size = count_pipes(m);
	m->cmd = ft_malloc(sizeof(t_cmd) * m->job_size, m->mem);
	if (!m->cmd)
		return (1);
	i = 0;
	while (i < m->job_size)
	{
		m->cmd[i].args = NULL;
		i++;
	}
	return (0);
}

bool	parser(t_mini *m)
{
	if (init_commands(m))
		return (1);
	if (parse_command_line(m))
		return (1);
	if (parse_redirect_and_heredoc(m))
		return (1);
	return (0);
}
