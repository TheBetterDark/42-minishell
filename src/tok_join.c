/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tokens.h"

static bool	merge_two_tokens(t_mini *m, t_token *cur)
{
	char	*cont;
	t_token	*tok;

	tok = cur->next;
	cont = cur->cont;
	cur->cont = ft_strjoin(cont, tok->cont);
	ft_lstadd_back(&m->mem, ft_lstnew(cur->cont));
	if (!cur->cont)
		return (1);
	ft_free(cont, m->mem);
	ft_free(tok->cont, m->mem);
	cur->end_pos = tok->end_pos;
	cur->next = tok->next;
	ft_free(tok, m->mem);
	return (0);
}

bool	merge_adjacent_tokens(t_mini *m)
{
	t_token	*cur;

	cur = m->t_head;
	while (cur->next)
	{
		if (cur->end_pos + 1 == cur->next->pos && cur->next->end_pos != -1)
		{
			if (merge_two_tokens(m, cur))
				return (1);
		}
		else
			cur = cur->next;
	}
	m->t_tail = cur;
	return (0);
}
