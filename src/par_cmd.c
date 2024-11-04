/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

static int	get_arg_size(t_token *current)
{
	int	ct;

	ct = 1;
	while (current)
	{
		if (current->type == PIPE)
			break ;
		if (current->type == COMMAND || current->type == ARG)
			if (current->cont)
				if (current->cont[0])
					ct++;
		current = current->next;
	}
	return (ct);
}

static void	set_command_args(t_mini *m, int idx, int arg_size, t_token *cur)
{
	int		i;

	i = 0;
	while (i < arg_size - 1)
	{
		if (cur->type == COMMAND || cur->type == ARG)
			if (cur->cont)
				if (cur->cont[0])
					m->cmd[idx].args[i++] = cur->cont;
		cur = cur->next;
	}
	m->cmd[idx].args[i] = NULL;
	m->cmd[idx].if_executable = 1;
}

bool	parse_command_line(t_mini *m)
{
	int		i;
	int		arg_size;
	t_token	*cur;

	cur = m->t_head->next;
	i = 0;
	while (i < m->job_size && cur)
	{
		arg_size = get_arg_size(cur);
		if (arg_size != 1)
		{
			m->cmd[i].args = ft_malloc(arg_size * sizeof(char *), m->mem);
			if (!m->cmd[i].args)
				return (1);
			set_command_args(m, i, arg_size, cur);
		}
		cur = find_cmd_after_pipe(cur);
		i++;
	}
	return (0);
}
