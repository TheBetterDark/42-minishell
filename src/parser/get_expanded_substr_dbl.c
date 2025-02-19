/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expanded_substr_dbl.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:42:46 by muabdi            #+#    #+#             */
/*   Updated: 2025/02/19 14:24:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

char	*append_symbols_dbl(char *expand, char *name, int *i)
{
	char	*join;
	char	*substr;
	int		start;

	start = *i;
	while (name[*i] && name[*i] != '\"' && name[*i] != '$')
		(*i)++;
	substr = ft_substr(name, start, *i - start);
	join = ft_strjoin(expand, substr);
	free(substr);
	free(expand);
	return (join);
}

char	*get_expanded_substr_dbl(char *name, int *i, t_data *data)
{
	char	*expand;
	char	*substr;
	int		start;

	(*i)++;
	start = *i;
	if (name[*i] == '?')
	{
		(*i)++;
		substr = ft_strdup("?");
	}
	else
	{
		while (name[*i] && name[*i] != '\"'
			&& (ft_isalnum(name[*i]) || name[*i] == '_'))
			(*i)++;
		substr = ft_substr(name, start, *i - start);
	}
	expand = find_environment_value(substr, data);
	free(substr);
	if (name[*i] && name[*i] != '\"' && name[*i] != '$')
		return (append_symbols_dbl(expand, name, i));
	return (expand);
}
