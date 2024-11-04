/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 17:36:57 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tokens.h"

static bool	new_tok(t_mini *m, char *cont, int size, int idx)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), m->mem);
	if (!new)
		return (1);
	new->next = NULL;
	new->cont = NULL;
	new->type = ARG;
	m->t_tail->next = new;
	m->t_tail = new;
	m->b_size++;
	new->cont = ft_malloc(size + 1, m->mem);
	if (!new->cont)
		return (1);
	ft_strlcpy(new->cont, cont, size + 1);
	new->end_pos = idx + size;
	new->pos = idx + 1;
	new->can_split = 0;
	return (0);
}

static int	mark_delims(int *pos, char *str, char *delims)
{
	int	num;
	int	i;
	int	j;

	if (ft_strlen(str) == 0 || !pos)
		return (-1);
	num = 0;
	i = 0;
	pos[num++] = -1;
	while (str[i])
	{
		j = 0;
		while (delims[j])
		{
			if (delims[j] == str[i])
				pos[num++] = i;
			j++;
		}
		i++;
	}
	pos[num] = ft_strlen(str);
	return (num);
}

bool	extract_tokens(t_mini *m, char *str, char *delims)
{
	int		*pos;
	int		num;
	int		i;

	pos = (int *)ft_malloc(sizeof(int) * (ft_strlen(str) + 2), m->mem);
	if (!pos)
		return (1);
	num = mark_delims(pos, str, delims);
	i = 0;
	while (i < num)
	{
		if (pos[i + 1] - pos[i] > 1)
		{
			if (new_tok(m, str + pos[i] + 1, pos[i + 1] - pos[i] - 1, pos[i]))
				return (1);
			get_env(m, m->t_tail, 1);
		}
		i++;
	}
	ft_free(pos, m->mem);
	return (0);
}

bool	tokenize_input(t_mini *m)
{
	if (extract_tokens(m, m->input, " \t\n\'|<>"))
		return (1);
	return (0);
}
