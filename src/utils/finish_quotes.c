/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:14:43 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 12:48:37 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static bool	finish_quotes_util(char **join, char **buf, char **str1,
				char quote);
char		*finish_quotes(char *input);

static bool	finish_quotes_util(char **join, char **buf, char **str1,
	char quote)
{
	*str1 = ft_strdup(*join);
	free(*join);
	ft_putstr_fd("> ", STDOUT_FILENO);
	*buf = get_next_line(STDIN_FILENO);
	*join = ft_strjoin(*str1, *buf);
	free(*str1);
	if (ft_strchr(*buf, quote))
		return (true);
	free(*buf);
	return (false);
}

char	*finish_quotes(char *input)
{
	char	quote;
	char	*buf;
	char	*str1;
	char	*join;
	bool	found;

	found = false;
	quote = get_last_quote(input);
	join = ft_strjoin(input, "\n");
	buf = NULL;
	str1 = NULL;
	if (quote == 'x')
	{
		free(join);
		return (NULL);
	}
	while (!found)
	{
		found = finish_quotes_util(&join, &buf, &str1, quote);
	}
	return (join);
}
