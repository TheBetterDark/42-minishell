/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:58:29 by smoore            #+#    #+#             */
/*   Updated: 2025/02/12 19:30:51 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void		builtin_exit(t_data *data);

static bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static void	check_exit_args(t_cmd *cmd)
{
	if (cmd->cmdv[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		return ;
	}
	if (!ft_isnumber(cmd->cmdv[1]))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n",
			cmd->cmdv[1]);
		exit(2);
	}
}

void	builtin_exit(t_data *data)
{
	int	exit_stat;

	if (data->cmds && data->cmds->cmdv && data->cmds->cmdv[1])
	{
		check_exit_args(data->cmds);
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
