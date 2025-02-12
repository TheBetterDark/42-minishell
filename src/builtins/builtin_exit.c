/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:58:29 by smoore            #+#    #+#             */
/*   Updated: 2025/02/12 18:43:50 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	builtin_exit(t_data *data);

// TODO: Error check if arguments are not numbers
void	builtin_exit(t_data *data)
{
	int	exit_stat;

	if (data->cmds && data->cmds->cmdv && data->cmds->cmdv[1])
	{
		if (data->cmds->cmdv[2])
		{
			ft_printf("minishell: exit: too many arguments\n");
			return ;
		}
		exit_stat = ft_atoi(data->cmds->cmdv[1]);
	}
	else
		exit_stat = data->exit_stat;
	ft_str_arr_free(&data->env);
	free_minishell(data);
	if (data->pwd)
		free(data->pwd);
	close(data->saved_stdin);
	close(data->saved_stdout);
	free(data);
	ft_printf("exit\n");
	exit(exit_stat);
}
