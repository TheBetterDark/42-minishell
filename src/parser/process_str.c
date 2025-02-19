/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:38:06 by smoore            #+#    #+#             */
/*   Updated: 2025/02/18 17:28:49 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

char	*process_str(char *name, t_data *data);
char	*process_substr(char *name, int *i, t_data *data);
char	*handle_single_quotes(char *name, int *i);
char	*handle_double_quotes(char *name, int *i, t_data *data);
char	*handle_non_quotes(char *name, int *i, t_data *data);

char	*handle_single_quotes(char *name, int *i)
{
	char	*substr;
	int		start;

	substr = NULL;
	if (name[*i] == '\'')
	{
		(*i)++;
		start = *i;
		while (name[*i] && name[*i] != '\'')
			(*i)++;
		substr = ft_substr(name, start, *i - start);
		if (name[*i] && name[*i] == '\'')
			(*i)++;
		return (substr);
	}
	return (NULL);
}

char	*handle_double_quotes(char *name, int *i, t_data *data)
{
	char	*substr;
	char	*expand;
	int		start;

	if (name[*i] == '\"')
	{
		(*i)++;
		start = *i;
		while (name[*i] && name[*i] != '\"')
			(*i)++;
		substr = ft_substr(name, start, *i - start);
		expand = try_expand_dup(substr, data, true);
		free(substr);
		if (name[*i] && name[*i] == '\"')
			(*i)++;
		return (expand);
	}
	return (NULL);
}

char	*handle_non_quotes(char *name, int *i, t_data *data)
{
	char	*substr;
	char	*expand;
	int		start;

	start = *i;
	while (name[*i] && !is_quote(name[*i]))
		(*i)++;
	substr = ft_substr(name, start, (*i) - start);
	expand = try_expand_dup(substr, data, false);
	free(substr);
	return (expand);
}

char	*process_substr(char *name, int *i, t_data *data)
{
	if (!name[*i])
		return (NULL);
	else if (name[*i] == '\'')
		return (handle_single_quotes(name, i));
	else if (name[*i] == '\"')
		return (handle_double_quotes(name, i, data));
	else
		return (handle_non_quotes(name, i, data));
}

char	*process_str(char *name, t_data *data)
{
	char	*result;
	char	*segment;
	char	*tmp;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (name[i])
	{
		tmp = ft_strdup(result);
		free(result);
		segment = process_substr(name, &i, data);
		if (!segment)
		{
			free(tmp);
			break ;
		}
		result = ft_strjoin(tmp, segment);
		free(tmp);
		free(segment);
	}
	return (result);
}
