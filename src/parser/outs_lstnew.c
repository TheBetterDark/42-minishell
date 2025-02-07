/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outs_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:37:54 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 14:22:20 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	outs_lstclear(t_outs **head);
void	outs_lstadd_back(t_outs **head, t_outs *new);
t_outs	*outs_lstnew(t_token *cur);

void	outs_lstclear(t_outs **head)
{
	t_outs	*cur;
	t_outs	*next;

	if (*head == NULL)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		if (cur->trunc_fn)
			free(cur->trunc_fn);
		cur->trunc_fn = NULL;
		if (cur->append_fn)
			free(cur->append_fn);
		cur->append_fn = NULL;
		free(cur);
		cur = next;
	}
	*head = NULL;
}

void	outs_lstadd_back(t_outs **head, t_outs *new)
{
	t_outs	*cur;

	if (*head == NULL || !new)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

t_outs	*outs_lstnew(t_token *cur)
{
	t_outs	*new;

	new = malloc(sizeof(t_outs));
	if (!new)
		return (NULL);
	new->trunc_fn = NULL;
	new->append_fn = NULL;
	new->next = NULL;
	if (cur->type == FN_APPEND)
		new->append_fn = ft_strdup(cur->str);
	else if (cur->type == FN_TRUNC)
		new->trunc_fn = ft_strdup(cur->str);
	return (new);
}
