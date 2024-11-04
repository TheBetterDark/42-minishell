/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

static void	cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (errno == 2)
		exit(127);
	exit(1);
}

static void	no_such_file(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}

static void	exe_absolute(t_mini *m, int idx)
{
	check_if_dir(m->cmd[idx].args[0]);
	execve(m->cmd[idx].args[0], m->cmd[idx].args, __environ);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(m->cmd[idx].args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	if (errno == 13)
		exit(126);
	if (errno == 2)
		exit(127);
	exit(errno);
}

static void	exe_relative(t_mini *m, int idx)
{
	int			i;
	char		**path;

	path = get_path(m, m->cmd[idx].args[0]);
	execute_builtin(m, idx, 0);
	if (!path)
		no_such_file(m->cmd[idx].args[0]);
	i = 0;
	while (path[i])
	{
		check_if_dir(path[i]);
		if (access(path[i], X_OK) == 0)
		{
			execve(path[i], m->cmd[idx].args, __environ);
			perror("minishell");
			exit(errno);
		}
		i++;
	}
}

void	execute_cmd(t_mini *m, int idx)
{
	if (ft_strchr(m->cmd[idx].args[0], '/'))
		exe_absolute(m, idx);
	else
		exe_relative(m, idx);
	cmd_not_found(m->cmd[idx].args[0]);
}
