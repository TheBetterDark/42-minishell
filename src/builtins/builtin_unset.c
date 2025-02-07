/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 20:35:26 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	builtin_unset(t_data *data, char *unset_str);

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
* @brief Remove an environment variable
*
* @param data The data structure
* @param unset_str The environment variable to remove
*/
void	builtin_unset(t_data *data, char *unset_str)
{
	char	*env_value;
	char	**new_env;

	if (!unset_str)
		return ;
	env_value = find_environment_value(unset_str, data);
	if (!env_value || terms_match("", env_value))
		return ;
	if ((ft_str_arr_has((const char **)data->env, unset_str)) == false)
		return ;
	new_env = ft_str_arr_minus((const char **)data->env, unset_str);
	if (!new_env)
	{
		perror("unset failed");
		exit(EXIT_FAILURE);
	}
	ft_str_arr_free(&data->env);
	data->env = new_env;
}
