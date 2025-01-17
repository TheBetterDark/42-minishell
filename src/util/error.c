/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:28:21 by muabdi            #+#    #+#             */
/*   Updated: 2025/01/17 09:25:22 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	handle_error_parent(t_data *data, char *msg, int err_num,
	bool exit_stat)
{
	if (msg)
	{
		ft_putstr_fd(SHELL_PROMPT, STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	else
		perror(SHELL_PROMPT);
	if (exit_stat)
		exit_minishell(data, err_num);
	else
		data->exit_stat = err_num;
}

void	handle_error_child(t_data *data, char *msg, int err_num, bool exit_stat)
{
	if (msg)
	{
		ft_putstr_fd(SHELL_PROMPT, STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	else
		perror(SHELL_PROMPT);
	if (exit_stat)
	{
		if (data)
		{
			cleanup_minishell(data);
			if (data->env)
				ft_free_str_arr(&data->env);
			free(data);
		}
		exit(exit_stat);
	}
	else
		data->exit_stat = err_num;
}
