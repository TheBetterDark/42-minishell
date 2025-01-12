/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_command_line_split.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 15:46:04 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	handle_quotes(const char *str, int *pos)
{
	if (str[*pos] == '\'')
	{
		(*pos)++;
		while (str[*pos] && str[*pos] != '\'')
			(*pos)++;
		if (str[*pos] == '\'')
			(*pos)++;
	}
	else if (str[*pos] == '\"')
	{
		(*pos)++;
		while (str[*pos] && str[*pos] != '\"')
			(*pos)++;
		if (str[*pos] == '\"')
			(*pos)++;
	}
}

static void	handle_special_chars(const char *str, int *pos)
{
	char	tmp;

	if (str[*pos] == '>' || str[*pos] == '<')
	{
		tmp = str[*pos];
		(*pos)++;
		if (str[*pos] && str[*pos] == tmp)
			(*pos)++;
	}
}

static void	discern_words(const char *str, int *pos)
{
	if (str[*pos] && (str[*pos] == '\'' || str[*pos] == '\"'))
	{
		handle_quotes(str, pos);
	}
	else if (str[*pos] && (str[*pos] == '>' || str[*pos] == '<'))
	{
		handle_special_chars(str, pos);
	}
	else
	{
		while (str[*pos] && !is_blank(str[*pos]) && str[*pos] != '\''
			&& str[*pos] != '\"')
			(*pos)++;
	}
}

static void	write_words(char **toks, const char *str, t_data *d)
{
	int	pos;
	int	start;
	int	len;

	pos = 0;
	start = 0;
	while (str[pos])
	{
		while (str[pos] && is_blank(str[pos]))
			pos++;
		start = pos;
		discern_words(str, &pos);
		len = pos - start;
		if (len > 0)
		{
			*toks = ft_substr(str, start, len);
			if (!*toks)
				exit(1);
		}
		if (*toks[0] == '$' && ft_strlen(*toks) > 1)
			*toks = try_env_value(*toks, d->env, d->exit_stat);
		toks++;
	}
}

char	**command_line_split(char *input, t_data *d)
{
	char	**toks;
	int		count;

	count = count_words(input);
	toks = malloc(sizeof(char *) * (count + 1));
	if (!toks)
	{
		perror("toks malloc");
		return (NULL);
	}
	write_words(toks, input, d);
	toks[count] = NULL;
	return (toks);
}
