/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tokens.h"

static bool	new_tok(t_mini *m, int pos)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), m->mem);
	if (!new)
		return (1);
	new->next = NULL;
	new->cont = NULL;
	m->t_tail->next = new;
	m->t_tail = new;
	m->b_size++;
	new->end_pos = -1;
	new->pos = pos;
	new->can_split = 0;
	return (0);
}

static bool	right_shift(t_mini *m, int *i)
{
	if (m->input[*i + 1] == '>')
	{
		if (new_tok(m, *i))
			return (1);
		m->t_tail->type = APPEND;
		(*i)++;
	}
	else
	{
		if (new_tok(m, *i))
			return (1);
		m->t_tail->type = REDIR_OUT;
	}
	return (0);
}

static bool	left_shift(t_mini *m, int *i)
{
	if (m->input[*i + 1] == '<')
	{
		if (new_tok(m, *i))
			return (1);
		m->t_tail->type = HEREDOC;
		(*i)++;
	}
	else
	{
		if (new_tok(m, *i))
			return (1);
		m->t_tail->type = REDIR_IN;
	}
	return (0);
}

bool	redirection(t_mini *m)
{
	int	i;

	i = 0;
	while (m->input[i])
	{
		if (m->input[i] == '>')
		{
			if (right_shift(m, &i))
				return (1);
		}
		else if (m->input[i] == '<')
			if (left_shift(m, &i))
				return (1);
		i++;
	}
	return (0);
}
