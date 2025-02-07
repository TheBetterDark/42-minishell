/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_environment_value.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:37:00 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 14:42:41 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

char	*get_key(char *env_cur);
char	*search_for_env_match(char *key, char **env);
char	*find_environment_value(char *key, t_data *data);

char	*get_key(char *env_cur)
{
	char	*key;
	int		i;

	i = 0;
	while (env_cur[i])
	{
		if (env_cur[i] == '=')
		{
			key = ft_substr(env_cur, 0, i);
			if (word_match(key, ""))
			{
				perror("export \"\"= not a valid identifier");
				return (key);
			}
			return (key);
		}
		i++;
	}
	return (NULL);
}

char	*search_for_env_match(char *key, char **env)
{
	char	**env_cur;
	char	*potential_key;
	char	*matched_value;
	char	*result;

	env_cur = env;
	while (*env_cur)
	{
		potential_key = get_key(*env_cur);
		if (word_match(potential_key, key))
		{
			matched_value = ft_strchr(*env_cur, '=') + 1;
			result = ft_strdup(matched_value);
			free(potential_key);
			return (result);
		}
		free(potential_key);
		env_cur++;
	}
	return (ft_strdup(""));
}

char	*find_environment_value(char *key, t_data *data)
{
	char	*value;

	value = NULL;
	if (word_match(key, "?"))
		return (ft_itoa(data->exit_stat));
	if (key)
		value = search_for_env_match(key, data->env);
	if (!value)
		value = ft_strdup("");
	return (value);
}
