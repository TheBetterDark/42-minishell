/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:35:47 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 13:35:48 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	tok_lstclear(t_token **head);
void	tok_lstadd_back(t_token **head, t_token *new);
t_token	*tok_lstlast(t_token *cur);
t_token	*tok_lstnew(char *word);

void	tok_lstclear(t_token **head)
{
	t_token	*cur;
	t_token	*next;

	if (*head == NULL)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		free(cur->str);
		free(cur);
		cur = next;
	}
	*head = NULL;
}

t_token	*tok_lstlast(t_token *cur)
{
	if (!cur)
		return (NULL);
	while (cur)
	{
		if (!cur->next)
			return (cur);
		cur = cur->next;
	}
	return (cur);
}

void	tok_lstadd_back(t_token **head, t_token *new)
{
	t_token	*cur;

	if (*head == NULL || !new)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->prev = cur;
}

t_token	*tok_lstnew(char *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(word);
	new->next = NULL;
	new->prev = NULL;
	new->type = ARG;
	return (new);
}
