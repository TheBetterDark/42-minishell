/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_count_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/27 15:51:20 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

bool	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	find_quote_delim(char *str, int *i, char quote_mark, char other_mark)
{
	(*i)++;
	while (str[*i] && str[*i] != quote_mark)
		(*i)++;
	(*i)++;
	if (str[*i] == '\'')
		while (str[*i] && str[*i] != quote_mark)
			(*i)++;
	else if (str[*i] == other_mark)
		while (str[*i] && str[*i] != other_mark)
			(*i)++;
	else if (!is_space(str[*i]))
		while (str[*i] && !is_space(str[*i]))
			(*i)++;
}

static bool	is_quoted(char *str, int *i, char quote_mark)
{
	char	other_mark;

	if (quote_mark == '\'')
		other_mark = '\"';
	else if (quote_mark == '\"')
		other_mark = '\'';
	if (str[*i] == quote_mark)
	{
		find_quote_delim(str, i, quote_mark, other_mark);
		return (true);
	}
	return (false);
}

static void find_word_delim(char *str, int *i, int *count)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
	{
		(*count)++;
		(*i)++;
		if ((str[*i] == '>' && str[*i - 1] == '>')
			|| (str[*i] == '<' && str[*i - 1] == '<'))
			(*i)++;
	}
	else if (is_quoted(str, i, '\''))
		(*count)++;
	else if (is_quoted(str, i, '\"'))
		(*count)++;
	else if (!is_space(str[*i]))
	{
		(*count)++;
		while (str[*i] && !is_space(str[*i]))
			(*i)++;
	}
}

int	count_words(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
		find_word_delim(str, &i, &count);
	return (count);
}
