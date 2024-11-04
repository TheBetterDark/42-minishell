/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

void	execute_builtin(t_mini *m, int idx, bool is_print)
{
	if (!ft_strncmp(m->cmd[idx].args[0], "echo", 5))
		b_echo(m, idx);
	if (!ft_strncmp(m->cmd[idx].args[0], "cd", 3))
		b_cd(m, idx);
	if (!ft_strncmp(m->cmd[idx].args[0], "pwd", 4))
		b_pwd(m, 1);
	if (!ft_strncmp(m->cmd[idx].args[0], "export", 7))
		b_export(m, idx);
	if (!ft_strncmp(m->cmd[idx].args[0], "unset", 6))
		b_unset(m, idx);
	if (!ft_strncmp(m->cmd[idx].args[0], "env", 4))
		b_env(m, idx);
	if (!ft_strncmp(m->cmd[idx].args[0], "exit", 5))
		b_exit(m, idx, is_print);
}
