/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:14:14 by muabdi            #+#    #+#             */
/*   Updated: 2025/01/12 20:25:33 by muabdi           ###   ########.fr       */
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
	printf("exit\n");
	exit(exit_status);
}
