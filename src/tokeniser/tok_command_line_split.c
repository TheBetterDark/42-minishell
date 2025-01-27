/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_command_line_split.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/27 15:53:03 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	handle_quote(char *str, int *i, char delim);
static void handle_non_quote(char *str, int *i);
static int	find_tok_str_delim(char *str, int *i);


static void	handle_quote(char *str, int *i, char delim)
{
	char non_delim;

	non_delim = '\0';
	if (delim == '\'')
		non_delim = '\"';
	else if (delim == '\"')
		non_delim = '\'';
	find_quote_delim(str, i, delim, non_delim);
}

static void handle_non_quote(char *str, int *i)
{
	while (str[*i] && !is_space(str[*i]) && str[*i] != '\''
		&& str[*i] != '\"')
		(*i)++;
	if (str[*i] == '\'')
		handle_quote(str, i, str[*i]);
	else if (str[*i] == '\"')
		handle_quote(str, i, str[*i]);
}

static int	find_tok_str_delim(char *str, int *i)
{
	int	start;	

	start = *i;
	if (str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
	{
		(*i)++;
		if ((str[*i] == '>' && str[*i - 1] == '>')
			|| (str[*i] == '<' && str[*i - 1] == '<'))
			(*i)++;
	}
	else if (str[*i] == '\'')
		handle_quote(str, i, str[*i]);
	else if (str[*i] == '\"')
		handle_quote(str, i, str[*i]);
	else if (!is_space(str[*i]))
		handle_non_quote(str, i);
	return (start);
}

char	**command_line_split(char *input, t_data *data)
{
	char	**tok_strs;
	int		size;
	int		start;
	int		ct;
	int		i;

	size = count_words(input);
	if (size == -1)
		return (handle_error_parent(data, ERR_UNCLOSED_QUOTES, 258, false),
			NULL);
	tok_strs = malloc(sizeof(char *) * (size + 1));
	if (!tok_strs)
		return (handle_error_parent(data, ERR_OUT_OF_MEMORY, 12, true), NULL);
	i = 0;
	ct = 0;
	while (ct < size)
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		start = find_tok_str_delim(input, &i);	
		tok_strs[ct] = ft_substr(input, start, i - start);
		ct++;
	}
	tok_strs[ct] = NULL;
	return (tok_strs);
}
