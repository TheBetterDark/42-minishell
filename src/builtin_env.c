/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

void	b_env(t_mini *m, int idx)
{
	int	i;

	if (m->cmd[idx].args[1])
	{
		ft_putstr_fd("minishell: we don't handle options or arguments.\n", 2);
		exit(1);
	}
	i = 0;
	while (__environ[i])
		printf("%s\n", __environ[i++]);
	exit(0);
}
