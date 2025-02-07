/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 14:55:57 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	builtin_export(t_data *data, char *export_str);

/*
* @brief Add a new environment variable
*
* @param data The data structure
*/

void	builtin_export(t_data *data, char *export_str)
{
	char	**new_env;

	if (!ft_strchr(export_str, '='))
	{
		data->exit_stat = 1;
		return ;
	}
	new_env = ft_str_arr_add((const char **)data->env, export_str);
	if (!new_env)
	{
		perror("export failed");
		exit(EXIT_FAILURE);
	}
	ft_str_arr_free(&data->env);
	data->env = new_env;
}
