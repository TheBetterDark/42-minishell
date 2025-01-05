/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_double_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:42:24 by smoore            #+#    #+#             */
/*   Updated: 2025/01/05 15:33:58 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

char	*get_key(char *str);
char	*find_env_var(char *str, char **env);
char	*try_env_value(char *subquote, char **env, int exit_stat);

char	*get_key(char *str)
{
	int		pos;
	char	*key;

	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '=')
		{
			key = ft_substr(str, 0, pos);
			if (terms_match("", key))
			{
				perror("export `""= not a valid identifier");
				return (key);
			}
			return (key);
		}
		pos++;
	}
	return (NULL);
}

char	*find_env_var(char *str, char **env)
{
	char	**tmp;
	char	*key;
	char	*expanded_var;

	tmp = env;
	while (*tmp)
	{
		key = get_key(*tmp);
		if (terms_match(key, str))
		{
			expanded_var = ft_strchr(*tmp, '=') + 1;
			free(key);
			return (expanded_var);
		}
		free(key);
		tmp++;
	}
	return ("");
}

char	*try_env_value(char *subquote, char **env, int exit_stat)
{
	char	*env_value;

	env_value = NULL;
	if (terms_match(subquote, "$?"))
	{
		free(subquote);
		subquote = ft_itoa(exit_stat);
	}
	else if (subquote[0] == '$')
	{
		env_value = find_env_var(subquote + 1, env);
		if (env_value)
		{
			free(subquote);
			subquote = ft_strdup(env_value);
			if (!subquote)
				subquote = ft_strdup("");
		}
		else
		{
			free(subquote);
			subquote = ft_strdup("");
		}
	}
	return (subquote);
}

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

char	*dup_double_quotes(char *str, t_data *d)
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
		subquote = try_env_value(subquote, d->env, d->exit_stat);
		prev = result;
		result = ft_strjoin(result, subquote);
		free(subquote);
		if (!result)
		{
			free(prev);
			return (NULL);
		}
		free(prev);
	}
	return (result);
}
