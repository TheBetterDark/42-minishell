/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

static void	b_export_error(t_mini *m, char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	m->exit_status = 1;
}

void	b_export(t_mini *m, int idx)
{
	int	i;
	int	j;

	i = 0;
	while (m->cmd[idx].args[++i])
	{
		j = 0;
		while (m->cmd[idx].args[i][j])
		{
			if (m->cmd[idx].args[i][j] == '=' && j != 0)
			{
				m_export(m, m->cmd[idx].args[i], "export");
				break ;
			}
			if (!ft_isalpha(m->cmd[idx].args[i][0])
				|| !ft_isalnum(m->cmd[idx].args[i][j]))
			{
				b_export_error(m, m->cmd[idx].args[i]);
				break ;
			}
			j++;
		}
	}
	if (m->job_size != 1)
		exit(0);
}
