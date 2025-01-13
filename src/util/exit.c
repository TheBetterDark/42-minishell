/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:14:14 by muabdi            #+#    #+#             */
/*   Updated: 2025/01/13 10:58:32 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

/*
* @brief Exit the minishell
*
* @param data The data struct
*/
void	exit_minishell(t_data *data, int exit_status)

{
	if (data)
	{
		cleanup_minishell(data);
		if (data->env)
			ft_free_str_arr(&data->env);
		free(data);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_status);
}
