/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_command_line_split.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/03 19:02:28 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	discern_words(const char *str, int *pos)
{
	if (str[*pos] && str[*pos] == '\'')
	{
		(*pos)++;
		while (str[*pos] && str[*pos] != '\'')
			(*pos)++;
		if (str[*pos] == '\'')
			(*pos)++;
	}
	else if (str[*pos] && str[*pos] == '\"')
	{
		(*pos)++;
		while (str[*pos] && str[*pos] != '\"')
			(*pos)++;
		if (str[*pos] == '\"')
			(*pos)++;
	}
	else
		while (str[*pos] && !is_blank(str[*pos])
			&& str[*pos] != '\'' && str[*pos] != '\"')
			(*pos)++;
}

static void	write_words(char **toks, const char *str)
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
			{
				perror("ft_substr failed");
				exit(1);
			}
		}
		toks++;
	}
}

char	**command_line_split(char *input)
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
	write_words(toks, input);
	toks[count] = NULL;
	return (toks);
}
