/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:02:31 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 12:52:37 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

bool	word_match(char *word, char *check);
bool	is_blank(char c);
bool	is_symbol(char c);
bool	is_quote(char c);

bool	word_match(char *word, char *check)
{
	if (ft_strncmp(word, check, ft_strlen(word)) == 0)
		return (true);
	return (false);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_symbol(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
