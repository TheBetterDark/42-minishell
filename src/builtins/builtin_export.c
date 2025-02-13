/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/02/13 15:46:14 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static void	update_existing_var(char *cur_env_var, char *export_str);
static void	add_new_var(t_data *data, char *export_str);
void		builtin_export(t_data *data, char **export_str);

static void	update_existing_var(char *cur_env_var, char *export_str)
{
	size_t	new_value_len;

	new_value_len = strlen(export_str);
	if (new_value_len <= strlen(cur_env_var))
	{
		strncpy(cur_env_var, export_str, new_value_len);
		cur_env_var[new_value_len] = '\0';
	}
	else
	{
		char *new_var = strdup(export_str);
		if (!new_var)
		{
			perror("export failed");
			exit(EXIT_FAILURE);
		}
		free(cur_env_var);
		cur_env_var = new_var;
	}
}

static void	add_new_var(t_data *data, char *export_str)
{
	char	**new_env;

	new_env = ft_str_arr_add((const char **)data->env, export_str);
	ft_str_arr_free(&data->env);
	if (!new_env)
	{
		perror("minishell: export failed");
		exit(EXIT_FAILURE);
	}
	data->env = new_env;
}

void	builtin_export(t_data *data, char **export_str)
{
	char	*cur_env_var;

	export_str++;
	if (!*export_str)
	{
		print_env(data);
		return ;
	}
	while (*export_str)
	{
		if (!ft_strchr(*export_str, '='))
		{
			data->exit_stat = 1;
			return ;
		}
		cur_env_var = get_environment_variable(*export_str, data);
		if (cur_env_var)
			update_existing_var(cur_env_var, *export_str);
		else
			add_new_var(data, *export_str);
		export_str++;
	}
}
