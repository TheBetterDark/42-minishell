/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:38:44 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 13:38:46 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	cleanup_child(t_data *data, int exit_status);

void	cleanup_child(t_data *data, int exit_status)
{
	if (data)
	{
		free_minishell(data);
		ft_str_arr_free(&data->env);
		free(data);
	}
	exit(exit_status);
}
