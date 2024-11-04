/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

void	b_exit_numerr(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

bool	b_exit_checkover(char *num)
{
	if (ft_strlen(num) > 20)
		return (1);
	if (ft_strlen(num) == 20)
	{
		if (!ft_strncmp(num, "-9223372036854775808", 21))
			return (0);
		else
			return (1);
	}
	if (ft_strncmp(num, "9223372036854775807", 20) > 0)
		return (1);
	return (0);
}

bool	b_exit_checkdigits(char *num)
{
	if (num[0] == '+')
		num++;
	if (ft_isdigit_str(num))
		return (1);
	if (num[0] == '-' && ft_isdigit_str(num + 1) && ft_strlen(num) > 1)
		return (1);
	return (0);
}

static void	b_exit_subroutine(t_mini *m, int idx, int i, bool is_print)
{
	if (b_exit_checkdigits(m->cmd[0].args[1]))
	{
		if (i > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			if (!is_print)
				exit(1);
			else
				m->exit_status = 1;
		}
		else if (b_exit_checkover(m->cmd[idx].args[1]))
			b_exit_numerr(m->cmd[idx].args[1]);
		else
			exit(ft_atol(m->cmd[idx].args[1]));
	}
	else
		b_exit_numerr(m->cmd[idx].args[1]);
}

void	b_exit(t_mini *m, int idx, bool is_print)
{
	int	i;

	i = -1;
	while (m->cmd[idx].args[++i])
		;
	if (is_print)
		printf("exit\n");
	if (i >= 2)
		b_exit_subroutine(m, idx, i, is_print);
	else
		exit(0);
}
