/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/02/02 16:15:20 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static bool	handle_double_quote(char *s, int *i)
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

static bool	handle_single_quote(char *s, int *i)
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

static char	*substr_logic(char *s, int *i, t_data *data, char *substr)
{
	int		start;
	bool	quotes_closed;

	start = *i;
	quotes_closed = true;
	if (s[*i] == '\"')
	{
		quotes_closed = handle_double_quote(s, i);
		if (quotes_closed)
			substr = ft_substr(s, start + 1, (*i - start) - 1);
		substr = dup_double_quotes(substr, data);
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
	return (substr);
}

static char	*get_str(char *s, int *i, t_data *data)
{
	char	*substr;

	substr = NULL;
	substr = substr_logic(s, i, data, substr);
	if (!substr)
		return (NULL);
	return (substr);
}

char	*process_tok_cont(char *cont, t_data *data)
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
		if (!str1)
			return (NULL);
		str2 = get_str(cont, &i, data);
		if (!str2)
			return (NULL);
		join = ft_strjoin(str1, str2);
		free(str1);
		free(str2);
		if (!join)
			return (NULL);
		if (i > (int)ft_strlen(cont))
			break ;
	}
	return (join);
}
