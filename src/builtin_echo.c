/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

static void	b_echo_n(t_cmd exe, int i)
{
	while (exe.args[i])
	{
		printf("%s", exe.args[i++]);
		if (exe.args[i])
			printf(" ");
	}
	exit(0);
}

bool	skip_option(t_cmd exe, int *idx)
{
	size_t	i;
	bool	flag;

	flag = false;
	while (exe.args[*idx])
	{
		if (exe.args[*idx][0] == '-' && exe.args[*idx][1])
		{
			i = 0;
			while (exe.args[*idx][++i])
			{
				if (exe.args[*idx][i] == 'n')
					flag = true;
				else
					break ;
			}
			if (i == ft_strlen(exe.args[*idx]) && exe.args[*idx][i] != '-')
				(*idx)++;
			else
				break ;
		}
		else
			break ;
	}
	return (flag);
}

void	b_echo(t_mini *m, int idx)
{
	int		i;
	bool	flag;

	i = 1;
	flag = skip_option(m->cmd[idx], &i);
	if (flag)
		b_echo_n(m->cmd[idx], i);
	else
	{
		while (m->cmd[idx].args[i])
		{
			printf("%s", m->cmd[idx].args[i++]);
			if (m->cmd[idx].args[i])
				printf(" ");
		}
		printf("\n");
	}
	exit(0);
}
