/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/env_tok.h"

static bool	copy_cont(t_mini *m, t_token *tok, t_env *env, int i)
{
	char	*copy;

	copy = ft_strjoin(env->cont, &tok->cont[i]);
	if (!copy)
		return (1);
	ft_free(env->cont, m->mem);
	ft_lstadd_back(&m->mem, ft_lstnew(copy));
	env->cont = copy;
	return (0);
}

bool	copy_env(t_mini *m, t_env *env, char *env_cont)
{
	char	*copy;

	copy = ft_strjoin(env->cont, env_cont);
	if (!copy)
		return (1);
	ft_free(env->cont, m->mem);
	ft_lstadd_back(&m->mem, ft_lstnew(copy));
	env->cont = copy;
	return (0);
}

char	*get_cont(t_mini *m, char *name)
{
	char	*cont;

	if (ft_strncmp("?", name, 2) == 0)
	{
		cont = ft_ltoa(m->exit_status);
		ft_lstadd_back(&m->mem, ft_lstnew(cont));
	}
	else
		cont = getenv(name);
	return (cont);
}

static bool	handle_env(t_mini *m, t_token *tok, t_env *env)
{
	int		i;
	char	*cont;
	char	*name;

	i = -1;
	while (++i < env->num)
	{
		if (env->num - i > 1)
			tok->cont[env->idx[i + 1]] = 0;
		name = get_name(m, env, &tok->cont[env->idx[i] + 1], i);
		if (!name)
			return (1);
		cont = get_cont(m, name);
		if (cont == NULL)
			cont = "";
		copy_env(m, env, cont);
		copy_cont(m, tok, env, env->idx[i] + ft_strlen(name) + 1);
		if (ft_strncmp("?", name, 2) == 0)
			ft_free(cont, m->mem);
		ft_free(name, m->mem);
		if (env->num - i > 1)
			tok->cont[env->idx[i + 1]] = '$';
	}
	return (0);
}

bool	get_env(t_mini *m, t_token *tok, bool is_div)
{
	t_env	env;

	env.num = count(tok, is_div);
	if (env.num == 0)
		return (0);
	env.idx = ft_malloc(sizeof(int) * env.num, m->mem);
	if (!env.idx)
		return (1);
	get_idx(tok, &env);
	env.cont = ft_malloc(ft_strlen(tok->cont) + 1, m->mem);
	if (!env.cont)
		return (1);
	tok->cont[env.idx[0]] = 0;
	ft_strcpy(env.cont, tok->cont);
	tok->cont[env.idx[0]] = '$';
	if (handle_env(m, tok, &env))
		return (1);
	ft_free(tok->cont, m->mem);
	tok->cont = env.cont;
	ft_free(env.idx, m->mem);
	return (0);
}
