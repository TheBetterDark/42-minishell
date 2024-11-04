/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

bool	env_size_inc(t_mini *m, char *new_str)
{
	char	**new_env;
	char	*tmp;
	int		size;
	int		i;

	size = 2;
	while (__environ[size - 2])
		size++;
	new_env = ft_malloc(sizeof(char *) * size, m->env_vars);
	if (!new_env)
		return (1);
	i = 0;
	while (__environ[i])
	{
		new_env[i] = __environ[i];
		i++;
	}
	tmp = ft_strdup(new_str);
	ft_lstlast(m->env_vars)->next = ft_lstnew(tmp);
	new_env[i] = tmp;
	new_env[i + 1] = NULL;
	ft_free(__environ, m->env_vars);
	__environ = new_env;
	return (0);
}

bool	is_exist_export(t_mini *m, char *target)
{
	int		i;
	int		equal_mark;
	char	*tmp;

	equal_mark = 1;
	while (target[equal_mark])
		if (target[equal_mark++] == '=')
			break ;
	i = 0;
	while (__environ[i])
	{
		if (ft_strncmp(__environ[i], target, equal_mark) == 0)
		{
			ft_free(__environ[i], m->env_vars);
			tmp = ft_strdup(target);
			ft_lstlast(m->env_vars)->next = ft_lstnew(tmp);
			__environ[i] = tmp;
			return (1);
		}
		i++;
	}
	return (0);
}

void	m_export(t_mini *m, char *new_env, char *caller)
{
	if (!is_exist_export(m, new_env))
	{
		if (env_size_inc(m, new_env))
		{
			ft_putstr_fd("minishell: ", 2);
			perror(caller);
			if (m->job_size != 1)
				exit(errno);
		}
	}
}
