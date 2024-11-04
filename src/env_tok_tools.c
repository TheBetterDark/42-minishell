/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tok_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 16:35:25 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/env_tok.h"

static void	set_can_split(t_token *tok, bool can_split, int idx)
{
	if (idx > 0)
	{
		if (idx > 1)
		{
			if (tok->cont[idx - 1] != '=' && ft_isalpha(tok->cont[idx - 2]))
				tok->can_split = can_split;
			else
				tok->can_split = 0;
		}
		else
			tok->can_split = can_split;
	}
	else
		tok->can_split = can_split;
}

int	count(t_token *tok, bool can_split)
{
	int	i;
	int	ct;

	ct = 0;
	i = -1;
	while (tok->cont[++i])
	{
		if (tok->cont[i] == '$' && tok->cont[i + 1])
		{
			if (tok->cont[i + 1] != ' ')
			{
				if (i != 0)
					if (tok->cont[i - 1] == '\\' || tok->cont[i + 1] == '\0')
						continue ;
				if (i >= 2)
					if (tok->cont[i - 2] != '\\' && tok->cont[i - 1] == '$')
						continue ;
				if (i == 1 && tok->cont[i - 1] == '$')
					continue ;
				ct++;
				set_can_split(tok, can_split, i);
			}
		}
	}
	return (ct);
}

void	get_idx(t_token *tok, t_env *env)
{
	int	i;
	int	ct;

	ct = 0;
	i = -1;
	while (tok->cont[++i])
	{
		if (tok->cont[i] == '$')
		{
			if (i != 0)
				if (tok->cont[i - 1] == '\\' || tok->cont[i + 1] == '\0')
					continue ;
			if (i >= 2)
				if (tok->cont[i - 2] != '\\' && tok->cont[i - 1] == '$')
					continue ;
			if (i == 1)
				if (tok->cont[i - 1] == '$')
					continue ;
			env->idx[ct++] = i;
		}
	}
}

char	*get_stat_name(t_mini *m)
{
	char	*ans;

	ans = ft_strdup("?");
	if (!ans)
		return (NULL);
	ft_lstlast(m->mem)->next = ft_lstnew(ans);
	return (ans);
}

char	*get_name(t_mini *m, t_env *env, char *str, int idx)
{
	int		i;
	int		j;
	char	*ans;

	if (str[0] == '?')
		return (get_stat_name(m));
	i = 0;
	while ((ft_isalnum(str[i])) && str[i])
		i++;
	if (idx + 1 < env->num)
		if (i > env->idx[idx + 1])
			i = env->idx[idx + 1];
	ans = ft_malloc(i + 1, m->mem);
	if (!ans)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ans[j] = str[j];
		j++;
	}
	ans[j] = 0;
	return (ans);
}
