/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 18:18:41 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static void	print_env(t_data *data);
static void	error_util(void);
void		builtin_export(t_data *data, char **export_str);

static void	print_env(t_data *data)
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

static void	error_util(void)
{
	perror("export failed");
	exit(EXIT_FAILURE);
}

void	builtin_export(t_data *data, char **export_str)
{
	char	**new_env;

	export_str++;
	new_env = NULL;
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
		new_env = ft_str_arr_add((const char **)data->env, *export_str);
		if (!new_env)
			error_util();
		ft_str_arr_free(&data->env);
		data->env = new_env;
		export_str++;
	}
}
