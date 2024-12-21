/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/21 21:13:18 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	skyy_export(t_data *d, char *export_str)
{
	char	**new_env;

	new_env = ft_str_arr_add((const char **)d->env, export_str);
	if (!new_env)
	{
		perror("export failed");
		exit(EXIT_FAILURE);
	}
	ft_free_str_arr(d->env);
	d->env = ft_str_arr_dup((const char **)new_env);
	ft_free_str_arr(new_env);
}
