/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_quoting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tokens.h"

static bool	new_token(t_mini *m, int size, int pos)
{
	t_token	*new;
	int		i;

	new = ft_malloc(sizeof(t_token), m->mem);
	if (!new)
		return (1);
;

	ft_memset(new, 0, sizeof(t_token));
	m->t_tail->next = new;
	m->t_tail = new;
	m->a_size++;
	new->cont = ft_malloc(size, m->mem);
	if (!new->cont)
		return (1);
	ft_strlcpy(new->cont, m->input + pos + 1, size);
	new->end_pos = pos + size;
	new->pos = pos;
	new->type = ARG;
	i = 0;
	while (i <= size)
	{
		m->input[pos + i] = '\'';
		i++;
	}
	new->can_split = 0;
	return (0);
}

static bool	single_quotes(t_mini *m, int *pos)
{
	int	size;
	int	flag;

	size = 1;
	flag = 1;
	while (m->input[*pos + size])
	{
		if (m->input[*pos + size] == '\'')
		{
			if (new_token(m, size, *pos))
				return (1);
			*pos += size;
			flag = 0;
			break ;
		}
		size++;
	}
	if (flag)
		return (1);
	return (0);
}

static bool	double_quotes(t_mini *m, int *pos)
{
	int	size;
	int	flag;

	size = 1;
	flag = 1;
	while (m->input[*pos + size])
	{
		if (m->input[*pos + size] == '\"')
		{
			new_token(m, size, *pos);
			*pos += size;
			flag = 0;
			break ;
		}
		size++;
	}
	if (flag)
		return (1);
	get_env(m, m->t_tail, 0);
	return (0);
}

bool	handle_quotes(t_mini *m)
{
	int	i;

	i = 0;
	while (m->input[i])
	{
		if (m->input[i] == '\'')
		{
			if (single_quotes(m, &i))
				return (1);
		}
		else if (m->input[i] == '\"')
			if (double_quotes(m, &i))
				return (1);
		i++;
	}
	return (0);
}
