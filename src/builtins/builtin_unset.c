/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/02/19 18:55:34 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	builtin_unset(t_data *data, char **unset_str);

/*
* @brief Remove an environment variable
*
* @param data The data structure
* @param unset_str The environment variable to remove
*/
void	builtin_unset(t_data *data, char **unset_str)
{
	char	**new_env;
	char	*env_var;

	unset_str++;
	while (*unset_str)
	{
		if ((ft_str_arr_has((const char **)data->env, *unset_str)) == false)
			return ;
		env_var = find_env_match(*unset_str, data->env);
		if (!env_var)
		{
			printf("unset: `%s': not a valid identifier\n", env_var);
			return ;
		}
		new_env = ft_str_arr_minus((const char **)data->env, env_var);
		if (!new_env)
		{
			perror("unset failed");
			return ;
		}
		ft_str_arr_free(&data->env);
		data->env = new_env;
		unset_str++;
	}
}
