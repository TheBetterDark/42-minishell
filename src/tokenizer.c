/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 17:40:26 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tokens.h"

static bool	check_if_last_token_cntl_ops(t_mini *m)
{
	t_token	*current;

	current = m->t_head->next;
	while (current->next)
		current = current->next;
	if (current->type >= PIPE && current->type <= HEREDOC)
		return (1);
	return (0);
}

static bool	new_token(t_mini *m, char *cont, t_token *prev, t_token *now)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), m->mem);
	if (!new)
		return (1);
	new->next = now->next;
	new->cont = cont;
	new->type = ARG;
	prev->next = new;
	if (prev == m->t_tail)
		m->t_tail = new;
	m->a_size++;
	return (0);
}

static bool	add_split_toks(t_mini *m, t_token **prev, t_token *now, char **tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		ft_lstadd_back(&m->mem, ft_lstnew(tmp[i]));
		if (new_token(m, tmp[i], *prev, now))
			return (1);
		*prev = (*prev)->next;
		i++;
	}
	return (0);
}

static bool	divide_token(t_mini *m, t_token *prev, t_token *current)
{
	char	**tmp;

	while (current)
	{
		if (ft_strchr(current->cont, ' ') && current->can_split)
		{
			tmp = ft_split(current->cont, ' ');
			if (!tmp)
				return (1);
			if (add_split_toks(m, &prev, current, tmp))
				return (1);
			current = prev->next;
			free(tmp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return (0);
}

bool	tokenizer(t_mini *m)
{
	sig_ignore();
	if (handle_quotes(m))
		return (1);
	if (tokenize_input(m))
		return (1);
	merge_sort_tokens(m);
	if (tokenize_pipeline(m))
		return (1);
	merge_sort_tokens(m);
	if (tokenize_pipeline(m))
		if (redirection(m))
			return (1);
	merge_sort_tokens(m);
	if (tokenize_pipeline(m))
		if (merge_adjacent_tokens(m))
			return (1);
	if (divide_token(m, m->t_head, m->t_head->next))
		return (1);
	if (!m->t_head->next)
		return (1);
	assign_token_type(m);
	if (check_if_last_token_cntl_ops(m))
		return (1);
	return (0);
}
