/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 15:17:58 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	builtin_unset(t_data *data, char *unset_str);

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
	if ((ft_str_arr_has((const char **)data->env, unset_str)) == false)
		return ;
	env_value = find_environment_value(unset_str, data);
	if (!env_value)
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
