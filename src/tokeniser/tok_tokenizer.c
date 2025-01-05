/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/05 15:35:16 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

t_token	*tok_lstnew(char *word)
{
	t_token	*new_tok;

	new_tok = (t_token *)malloc(sizeof(t_token));
	if (!new_tok)
		return (NULL);
	new_tok->cont = ft_strdup(word);
	new_tok->next = NULL;
	new_tok->prev = NULL;
	return (new_tok);
}

void	tok_lstadd_back(t_token **head, t_token *new)
{
	t_token	*current;

	if (*head == NULL || !new)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_token	*tokenizer(t_data *d)
{
	char	**toks;
	char	**toks_start;
	t_token	*head;
	t_token	*new_tok;

	toks = command_line_split(d->input, d);
	if (!toks)
		return (NULL);
	toks_start = toks;
	head = NULL;
	while (*toks)
	{
		new_tok = tok_lstnew(*toks);
		tok_lstadd_back(&head, new_tok);
		toks++;
	}
	free_split(toks_start);
	tok_preliminary_type_assigner(head, d);
	tok_secondary_type_assigner(head);
	return (head);
}
