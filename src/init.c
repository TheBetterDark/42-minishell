/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	shell_malloc(t_mini *m)
{
	m->mem = ft_lstnew(NULL);
	if (!m->mem)
		return (1);
	m->t_head = ft_malloc(sizeof(t_token), m->mem);
	if (!m->t_head)
		return (1);
	m->path = ft_malloc(PATH_MAX, m->mem);
	if (!m->path)
		return (1);
	return (0);
}

bool	init_minishell(t_mini *m)
{
	m->a_size = 0;
	m->b_size = 0;
	m->input = NULL;
	if (shell_malloc(m))
		return (1);
	m->t_head->next = NULL;
	m->t_head->cont = NULL;
	m->t_head->end_pos = -100;
	m->t_tail = m->t_head;
	m->job_idx = 0;
	m->job_size = 0;
	m->is_print_sig = 1;
	return (0);
}

bool	init_environment(t_mini *m)
{
	char	**env_tmp;
	int		env_size;
	int		i;
	int		j;

	i = 0;
	while (__environ[i])
		i++;
	env_tmp = ft_malloc(sizeof(char *) * ++i, m->env_vars);
	if (!env_tmp)
		return (1);
	m->env_size = i;
	j = 0;
	while (j < i - 1)
	{
		env_size = ft_strlen(__environ[j]) + 1;
		env_tmp[j] = ft_malloc(env_size, m->env_vars);
		if (!env_tmp[j])
			return (1);
		ft_strlcpy(env_tmp[j], __environ[j], env_size);
		j++;
	}
	env_tmp[j] = NULL;
	__environ = env_tmp;
	return (0);
}
