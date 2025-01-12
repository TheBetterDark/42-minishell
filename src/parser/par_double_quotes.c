/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_double_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 19:49:30 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Get the substring between quotes
*
* @param str The string to get the substring from
* @param start The start of the substring
* @param pos The end of the substring
*
* @return The substring
*/
static char	*get_subquote(char *str, int *start, int *pos)
{
	char	*subquote;

	if (str[*pos] == '$')
	{
		*start = (*pos)++;
		while (str[*pos] && (str[*pos] != ' ' && str[*pos] != '$'))
			(*pos)++;
	}
	else
	{
		*start = *pos;
		while (str[*pos] && str[*pos] != '$')
			(*pos)++;
	}
	subquote = ft_substr(str, *start, *pos - *start);
	if (!subquote)
		return (NULL);
	return (subquote);
}

/*
* @brief Duplicate a string with double quotes
*
* @param str The string to duplicate
* @param data The data struct
*
* @return The duplicated string
*/
char	*dup_double_quotes(char *str, t_data *data)
{
	char	*subquote;
	char	*result;
	char	*prev;
	int		pos;
	int		start;

	pos = 0;
	start = 0;
	result = ft_strdup("");
	while (str[pos])
	{
		subquote = get_subquote(str, &start, &pos);
		subquote = try_env_value(subquote, data->env, data->exit_stat);
		prev = result;
		result = ft_strjoin(result, subquote);
		free(subquote);
		if (!result)
			return (free(prev), NULL);
		free(prev);
	}
	return (result);
}
