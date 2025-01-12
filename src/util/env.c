/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:13:49 by muabdi            #+#    #+#             */
/*   Updated: 2025/01/12 20:35:13 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

/*
* @brief Check if the terms match
*
* @param str1 The first term
* @param str2 The second term
*
* @return true if the terms match, false otherwise
*/
static bool	terms_match(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (false);
	if (ft_strcmp(str1, str2) != 0)
		return (false);
	return (true);
}

/*
* @brief Find the key in the environment variable
*
* @param str The environment variable
*
* @return char* The key
*/
static char	*get_key(char *str)
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

/*
* @brief Find the environment variable
*
* @param str The environment variable
* @param env The environment variable list
*
* @return char* The expanded variable
*/
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

/*
* @brief Try to get the environment value
*
* @param subquote The subquote
* @param env The environment variable list
* @param exit_stat The exit status
*
* @return char* The expanded variable
*/
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
