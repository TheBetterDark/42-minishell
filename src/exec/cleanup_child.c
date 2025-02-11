/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:38:44 by smoore            #+#    #+#             */
/*   Updated: 2025/02/11 13:23:10 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	cleanup_child(t_data *data, int exit_status);

void	cleanup_child(t_data *data, int exit_status)
{
	if (data)
	{
		free_minishell(data);
		ft_str_arr_free(&data->env);
		if (data->pwd)
			free(data->pwd);
		free(data);
	}
	exit(exit_status);
}
