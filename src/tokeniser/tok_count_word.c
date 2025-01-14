/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_count_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/14 13:32:35 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

/*
* @brief Finds the position of the quote in the string
*
* @param str The input string
* @param quote The quote character
*
* @return The position of the quote in the string
*/
static int	find_quote_pos(const char *str, char quote)
{
	int	pos;

	pos = 0;
	if (!str)
		return (1);
	while (str[pos])
	{
		if (str[pos] == quote)
			return (pos + 1);
		pos++;
	}
	return (1);
}

/*
* @brief Discerns the delimiter in the string
*
* @param str The input string
* @param pos The position in the string
*/
static void	discern_delim(const char *str, int *pos)
{
	char	tmp;

	if (is_quote(str[*pos], '\''))
	{
		(*pos)++;
		*pos += find_quote_pos(&str[*pos], '\'');
	}
	else if (is_quote(str[*pos], '\"'))
	{
		(*pos)++;
		*pos += find_quote_pos(&str[*pos], '\"');
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
		while (str[*pos] && !is_blank(str[*pos]) && !is_quote(str[*pos], '\'')
			&& !is_quote(str[*pos], '\"'))
			(*pos)++;
	}
}

/*
* @brief Handles the quotes in the string
*
* @param str The input string
* @param pos The position in the string
* @param in_double_quote The double quote flag
* @param in_single_quote The single quote flag
*
* @return True if the quote is handled, false otherwise
*/
static bool	handle_quotes(const char *str, int *pos, bool *in_double_quote,
		bool *in_single_quote)
{
	if (str[*pos] == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		(*pos)++;
		return (true);
	}
	if (str[*pos] == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		(*pos)++;
		return (true);
	}
	return (false);
}

/*
* @brief Counts the number of words in the string
*
* @param str The input string
*
* @return The number of words in the string
*/
int	count_words(const char *str)
{
	int		count;
	int		pos;
	bool	in_double_quote;
	bool	in_single_quote;

	if (!str || !*str)
		return (0);
	in_double_quote = false;
	in_single_quote = false;
	pos = 0;
	count = 0;
	while (str[pos])
	{
		while (is_blank(str[pos]))
			pos++;
		if (!str[pos])
			break ;
		if (handle_quotes(str, &pos, &in_double_quote, &in_single_quote))
			continue ;
		count++;
		discern_delim(str, &pos);
	}
	if (in_double_quote || in_single_quote)
		return (-1);
	return (count);
}
