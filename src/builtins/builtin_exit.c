/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:58:29 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 11:58:31 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	builtin_exit(t_data *data);

void	builtin_exit(t_data *data)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_str_arr_free(&data->env);
	free_minishell(data);
	free(data);
	exit(EXIT_SUCCESS);
}
