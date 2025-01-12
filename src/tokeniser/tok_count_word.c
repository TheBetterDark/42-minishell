/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_count_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 10:33:19 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	discern_delim(const char *str, int *pos)
{
	char	tmp;

	if (is_quote(str[*pos], '\''))
	{
		(*pos)++;
		*pos += handle_quote(&str[*pos], '\'');
	}
	else if (is_quote(str[*pos], '\"'))
	{
		(*pos)++;
		*pos += handle_quote(&str[*pos], '\"' );
	}
	else if (str[*pos] && (str[*pos] == '>' || str[*pos] == '<'))
	{
		tmp = str[*pos];
		(*pos)++;
		if (str[*pos] && str[*pos] == tmp)
			(*pos)++;
	}
	else
	{
		while (str[*pos] && !is_blank(str[*pos])
			&& !is_quote(str[*pos], '\'') && !is_quote(str[*pos], '\"'))
			(*pos)++;
	}
}

int	count_words(const char *str)
{
	int	count;
	int	pos;

	if (!str || !*str)
		return (0);
	pos = 0;
	count = 0;
	while (str[pos])
	{
		while (is_blank(str[pos]))
			pos++;
		if (str[pos])
		{
			count++;
			discern_delim(str, &pos);
		}
	}
	return (count);
}
