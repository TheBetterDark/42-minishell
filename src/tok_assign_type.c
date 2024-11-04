/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_assign_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tokens.h"

static void	assign_cmd_delim_file_type(t_token *now, t_token *prev)
{
	if (prev->type == PIPE || prev->type == FILENAME)
		now->type = COMMAND;
	else if (prev->type == DELIMETER)
		now->type = COMMAND;
	else if (prev->type == HEREDOC)
		now->type = DELIMETER;
	else if (prev->type == APPEND
		|| prev->type == REDIR_IN || prev->type == REDIR_OUT)
		now->type = FILENAME;
	else
		now->type = ARG;
}

//change prev type
static bool	if_fd_set(t_token *prev, int pos)
{
	if (ft_strlen(prev->cont) != 1)
		return (0);
	if (!ft_isdigit(prev->cont[0]))
		return (0);
	if (prev->end_pos + 1 != pos)
		return (0);
	prev->type = FD;
	return (1);
}

static void	type_init(t_mini *m, t_token **now, t_token **prev)
{
	(*now) = m->t_head->next;
	if (!(*now))
		return ;
	if ((*now)->next)
	{
		if ((*now)->next->type == REDIR_OUT
			|| (*now)->next->type == APPEND)
		{
			if (!if_fd_set((*now), (*now)->next->pos))
				(*now)->type = COMMAND;
		}
		else if ((*now)->end_pos != -1)
			(*now)->type = COMMAND;
	}
	else if ((*now)->end_pos != -1)
		(*now)->type = COMMAND;
	*prev = *now;
	(*now) = (*now)->next;
}

void	assign_token_type(t_mini *m)
{
	t_token	*cur;
	t_token	*prev;

	type_init(m, &cur, &prev);
	while (cur)
	{
		if (prev->type != COMMAND && cur->end_pos != -1)
			assign_cmd_delim_file_type(cur, prev);
		else if ((prev->type == ARG || prev->type == COMMAND)
			&& (cur->type >= 1 && cur->type <= 4))
			if_fd_set(prev, cur->pos);
		else if (cur->end_pos != -1)
			cur->type = ARG;
		prev = cur;
		cur = cur->next;
	}
}
