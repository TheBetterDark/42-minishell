/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:42:46 by muabdi            #+#    #+#             */
/*   Updated: 2025/02/19 13:26:46 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

char	*find_env_match(char *key, char **env)
{
	char	**env_cur;
	char	*potential_key;

	env_cur = env;
	while (*env_cur)
	{
		potential_key = get_key(*env_cur);
		if (word_match(potential_key, key))
		{
			free(potential_key);
			return (*env_cur);
		}
		free(potential_key);
		env_cur++;
	}
	return (NULL);
}

char	*get_environment_variable(char *env_var, t_data *data)
{
	char	*value;
	char	*key;

	value = NULL;
	if (env_var)
	{
		key = get_key(env_var);
		value = find_env_match(key, data->env);
		free(key);
	}
	if (!value)
		return (NULL);
	return (value);
}

void	print_env(t_data *data)
{
	char	**tmp;

	tmp = data->env;
	while (*tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(*tmp, STDOUT_FILENO);
		tmp++;
	}
}
