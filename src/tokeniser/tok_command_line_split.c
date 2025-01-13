/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_command_line_split.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/13 15:57:11 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

/*
* @brief Handles quotes in the input string
*
* @param str The input string
* @param pos The position in the string
*/
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

/*
* @brief Handles special characters in the input string
*
* @param str The input string
* @param pos The position in the string
*/
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

/*
* @brief Discerns words in the input string
*
* @param str The input string
* @param pos The position in the string
*/
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

/*
* @brief Writes words to the toks array
*
* @param toks The array of words
* @param str The input string
* @param data The data structure
*/
static void	write_words(char **toks, const char *str, t_data *data)
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
			if (*toks[0] == '$' && ft_strlen(*toks) > 1)
				*toks = try_env_value(*toks, data->env, data->exit_stat);
		}
		else
			*toks = NULL;
		toks++;
	}
}

/*
* @brief Splits the command line into words
*
* @param input The input string
* @param data The data structure
*
* @return The array of words
*/
char	**command_line_split(char *input, t_data *data)
{
	char	**toks;
	int		count;

	count = count_words(input);
	if (count == -1)
		return (handle_error(data, ERR_UNCLOSED_QUOTES, 258, false), NULL);
	toks = malloc(sizeof(char *) * (count + 1));
	if (!toks)
		return (handle_error(data, ERR_OUT_OF_MEMORY, EXIT_MEMORY, true), NULL);
	write_words(toks, input, data);
	toks[count] = NULL;
	return (toks);
}
