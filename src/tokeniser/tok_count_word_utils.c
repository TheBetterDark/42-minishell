/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_count_word_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/03 19:01:52 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

int		find_char_pos(const char *str, char target);
bool	is_quote(const char c, const char quote);
bool	is_blank(const char c);
int		handle_quote(const char *str, char quote);

int	find_char_pos(const char *str, char target)
{
	int	pos;

	pos = 0;
	if (!str)
		return (-1);
	while (str[pos])
	{
		if (str[pos] == target)
			return (pos);
		pos++;
	}
	return (-1);
}

bool	is_quote(const char c, const char quote)
{
	return (c == quote);
}

bool	is_blank(const char c)
{
	return (c == ' ' || c == '\t');
}

int	handle_quote(const char *str, char quote)
{
	int	quote_pos;

	quote_pos = find_char_pos(str, quote);
	if (quote_pos != -1)
		return (quote_pos + 1);
	return (1);
}
