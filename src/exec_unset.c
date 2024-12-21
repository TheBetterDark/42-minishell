/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/17 16:30:11 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

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
	ft_free_str_arr(d->env);
//	d->env = ft_str_arr_dup((const char **)new_env);
	d->env = new_env;
//	fr_free_str_arr(new_env);
	exit(EXIT_SUCCESS);
}
