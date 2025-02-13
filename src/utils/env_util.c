/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:42:46 by muabdi            #+#    #+#             */
/*   Updated: 2025/02/13 15:44:41 by muabdi           ###   ########.fr       */
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

	value = NULL;
	if (env_var)
		value = find_env_match(get_key(env_var), data->env);
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
