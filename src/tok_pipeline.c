/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tokens.h"

static bool	new_token(t_mini *m, int idx)
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
	new->cont = ft_malloc(2, m->mem);
	if (!new->cont)
		return (1);
	new->cont[0] = '|';
	new->cont[1] = '\0';
	new->end_pos = -1;
	new->pos = idx;
	new->type = PIPE;
	new->can_split = 0;
	return (0);
}

bool	tokenize_pipeline(t_mini *m)
{
	int	i;

	i = 0;
	while (m->input[i])
	{
		if (m->input[i] == '|')
			if (new_token(m, i))
				return (1);
		i++;
	}
	return (0);
}
