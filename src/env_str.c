/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/env_str.h"

static bool	copy_cont(t_mini *m, char **str, t_env *env, int i)
{
	char	*copy;

	copy = ft_strjoin(env->cont, *str + i);
	if (!copy)
		return (1);
	ft_free(env->cont, m->mem);
	ft_lstadd_back(&m->mem, ft_lstnew(copy));
	env->cont = copy;
	return (0);
}

static bool	handle_env_str(t_mini *m, char **str, t_env *env)
{
	int		i;
	char	*cont;
	char	*name;

	i = -1;
	while (++i < env->num)
	{
		if (env->num - i > 1)
			(*str)[env->idx[i + 1]] = 0;
		name = get_name(m, env, *str + env->idx[i] + 1, i);
		if (!name)
			return (1);
		cont = get_cont(m, name);
		if (cont == NULL)
			cont = "";
		copy_env(m, env, cont);
		copy_cont(m, str, env, env->idx[i] + ft_strlen(name) + 1);
		if (ft_strncmp("?", name, 2) == 0)
			ft_free(cont, m->mem);
		ft_free(name, m->mem);
		if (env->num - i > 1)
			(*str)[env->idx[i + 1]] = '$';
	}
	return (0);
}

bool	get_env_str(t_mini *m, char **str)
{
	t_env	env;

	env.num = count_str(*str);
	if (env.num == 0)
		return (0);
	env.idx = ft_malloc(sizeof(int) * env.num, m->mem);
	if (!env.idx)
		return (1);
	ft_lstadd_back(&m->mem, ft_lstnew(*str));
	get_idx_str(*str, &env);
	env.cont = ft_malloc(ft_strlen(*str) + 1, m->mem);
	if (!env.cont)
		return (1);
	(*str)[env.idx[0]] = 0;
	ft_strcpy(env.cont, *str);
	(*str)[env.idx[0]] = '$';
	if (handle_env_str(m, str, &env))
		return (1);
	ft_free(*str, m->mem);
	*str = env.cont;
	ft_free(env.idx, m->mem);
	return (0);
}
