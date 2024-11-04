/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

void	reset_env(t_mini *m, char **new_env, int tar_idx)
{
	int	i;

	i = -1;
	while (++i != tar_idx)
		new_env[i] = __environ[i];
	while (__environ[i + 1])
	{
		new_env[i] = __environ[i + 1];
		i++;
	}
	new_env[i] = NULL;
	ft_free(__environ[tar_idx], m->env_vars);
	__environ = new_env;
}

bool	env_size_dec(t_mini *m, char *target, int tar_len)
{
	char	**new_env;
	int		i;
	int		tar_idx;

	tar_idx = -1;
	i = 0;
	while (__environ[i])
	{
		if (ft_strncmp(__environ[i], target, tar_len) == 0)
			if (__environ[i][tar_len] == '=')
				tar_idx = i;
		i++;
	}
	new_env = ft_malloc(sizeof(char *) * i, m->env_vars);
	if (!new_env)
		return (1);
	if (tar_idx != -1)
		reset_env(m, new_env, tar_idx);
	else
		return (1);
	return (0);
}

void	m_unset(t_mini *m, char *target)
{
	if (env_size_dec(m, target, ft_strlen(target)))
	{
		if (errno == ENOMEM)
		{
			perror("minishell: unset:");
			m->exit_status = errno;
			if (m->job_size != 1)
				exit(errno);
		}
	}
}
