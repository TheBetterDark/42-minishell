/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/04 16:37:50 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	skyy_unset(t_data *d, char *unset_str)
{
	char	**new_env;

	if ((ft_str_arr_has((const char **)d->env, unset_str)) == false)
	{
		perror("unset failed");
		exit(EXIT_FAILURE);
	}
	new_env = ft_str_arr_minus((const char **)d->env, unset_str);
	if (!new_env)
	{
		perror("unset failed");
		exit(EXIT_FAILURE);
	}
	ft_free_str_arr(&d->env);
	d->env = new_env;
}
