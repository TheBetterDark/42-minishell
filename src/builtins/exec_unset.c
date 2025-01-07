/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/07 22:10:00 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static bool	find_env_value(char *subquote, char **env)
{
	char	*env_value;

	env_value = NULL;
	env_value = find_env_var(subquote, env);
	if (!env_value || terms_match("", env_value))
		return (false);
	return (true);
}

void	skyy_unset(t_data *d, char *unset_str)
{
	char	**new_env;

	if (!unset_str)
		return ;
	if (!find_env_value(unset_str, d->env))
		return ;
	if ((ft_str_arr_has((const char **)d->env, unset_str)) == false)
		return ;
	new_env = ft_str_arr_minus((const char **)d->env, unset_str);
	if (!new_env)
	{
		perror("unset failed");
		exit(EXIT_FAILURE);
	}
	ft_free_str_arr(&d->env);
	d->env = new_env;
}
