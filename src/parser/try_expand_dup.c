/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_expand_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:38:17 by smoore            #+#    #+#             */
/*   Updated: 2025/02/18 18:29:53 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

char	*get_plain_substr(char *name, int *i);
char	*get_expanded_substr(char *substr, int *i, t_data *data);
char	*try_expand_dup(char *substr, t_data *data, bool dbl);

char	*get_plain_substr(char *name, int *i)
{
	char	*substr;	
	int		start;

	substr = NULL;
	start = *i;
	while (name[*i] && name[*i] != '$')
		(*i)++;
	if (name[ft_strlen(name) - 1] == '$')
		(*i)++;
	substr = ft_substr(name, start, *i - start);
	return (substr);
}

char	*get_expanded_substr(char *name, int *i, t_data *data)
{
	char	*expand;	
	char	*substr;	
	int		start;

	substr = NULL;
	expand = NULL;
	(*i)++;
	start = *i;
	while (name[*i] && !is_blank(name[*i] && name[*i] != '?'))
	{
		if (name[*i] == '$')
			break ;
		(*i)++;
	}
	substr = ft_substr(name, start, *i - start);
	expand = find_environment_value(substr, data);
	free(substr);
	return (expand);
}

char	*try_expand_dup(char *name, t_data *data, bool is_dbl)
{
	char	*str1;
	char	*str2;
	char	*join;
	int		i;

	join = ft_strdup("");
	i = 0;
	while (name[i])
	{
		str1 = ft_strdup(join);
		free(join);
		if (name[i] == '$' && name[i + 1] != '$' && !is_dbl)
			str2 = get_expanded_substr(name, &i, data);
		else if (name[i] == '$' && name[i + 1] != '$' && is_dbl)
			str2 = get_expanded_substr_dbl(name, &i, data);
		else
			str2 = get_plain_substr(name, &i);
		join = ft_strjoin(str1, str2);
		free(str1);
		free(str2);
	}
	return (join);
}
