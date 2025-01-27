/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/27 17:08:17 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static bool handle_double_quote(char *s, int *i)
{
	(*i)++;
	while (s[*i])
	{
		if (s[*i] == '\"')
			return (true);	
		(*i)++;
	}
	return (false);
}

static bool handle_single_quote(char *s, int *i)
{
	(*i)++;
	while (s[*i])
	{
		if (s[*i] == '\'')
			return (true);
		(*i)++;
	}
	return (false);
}

static char	*get_str(char *s, int *i)
{
	int		start;
	char	*substr;
	bool	quotes_closed;

	start = *i;
	substr = NULL;
	quotes_closed = true;
	if (s[*i] == '\"')
	{
		quotes_closed = handle_double_quote(s, i);
		if (quotes_closed)
			substr = ft_substr(s, start + 1, (*i - start) - 1);
	}
	else if (s[*i] == '\'')
	{
		quotes_closed = handle_single_quote(s, i);
		if (quotes_closed)
			substr = ft_substr(s, start + 1, (*i - start) - 1);
	}
	else
	{
		while (s[*i] && s[*i] != '\'' && s[*i] != '\"')
			(*i)++;
		substr = ft_substr(s, start, *i - start);
	}
	if (!substr)
		return (NULL);
	return (substr);
}

char	*process_tok_cont(char *cont)
{
	char	*str1;
	char	*str2;
	char	*join;
	int		i;
	
	i = 0;
	join = ft_strdup("");
	while (cont[i])
	{
		str1 = ft_strdup(join);
		free(join);
		str2 = get_str(cont, &i);
		if (!str2)
			return (NULL);
		join = ft_strjoin(str1, str2);
		free(str1);
		free(str2);
		i++;
	}
	return (join);
}
