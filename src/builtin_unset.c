/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

void	b_unset(t_mini *m, int idx)
{
	int	i;

	i = 1;
	while (m->cmd[idx].args[i])
	{
		if (getenv(m->cmd[idx].args[i]))
			m_unset(m, m->cmd[idx].args[i]);
		else if (!(ft_isalpha(m->cmd[idx].args[i][0])&& ft_isalnum_str(m->cmd[idx].args[i] + 1)))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(m->cmd[idx].args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
	if (m->job_size != 1)
		exit(0);
}
