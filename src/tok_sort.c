/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tokens.h"

static void	init_merge_ptrs(t_mini *m, t_sort *s)
{
	int		i;
	t_token	*current;

	s->a_cur = m->t_head->next;
	current = m->t_head->next;
	i = 0;
	while (i++ < m->a_size)
		current = current->next;
	s->b_cur = current;
	s->a_i = 0;
	s->b_i = 0;
}

static void	merge_single_token(t_mini *m, t_sort *s)
{
	if (s->a_cur->pos > s->b_cur->pos)
	{
		s->b_i++;
		m->t_tail->next = s->b_cur;
		s->b_cur = s->b_cur->next;
	}
	else
	{
		s->a_i++;
		m->t_tail->next = s->a_cur;
		s->a_cur = s->a_cur->next;
	}
	m->t_tail = m->t_tail->next;
}

void	merge_sort_tokens(t_mini *m)
{
	t_sort	s;

	init_merge_ptrs(m, &s);
	m->t_tail = m->t_head;
	while (s.a_i < m->a_size && s.b_i < m->b_size)
		merge_single_token(m, &s);
	if (s.a_i == m->a_size)
	{
		m->t_tail->next = s.b_cur;
		while (s.b_i++ < m->b_size)
			m->t_tail = m->t_tail->next;
	}
	else
	{
		m->t_tail->next = s.a_cur;
		while (s.a_i++ < m->a_size)
			m->t_tail = m->t_tail->next;
	}
	m->t_tail->next = NULL;
	m->a_size += m->b_size;
	m->b_size = 0;
}
