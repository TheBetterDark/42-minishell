/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/16 17:10:32 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

t_token	*tok_lstnew(char *word)
{
	t_token	*new_tok;

	new_tok = malloc(sizeof(t_token));
	if (!new_tok)
		return (NULL);
	new_tok->cont = word;
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

t_token	*tokenizer(t_data *d)
{
	char	**toks;
	t_token	*head;
	t_token	*new_tok;

	toks = ft_split(d->input, ' ');
	ft_str_arr_out((const char **)toks);
	head = NULL;
	while (*toks)
	{
		new_tok = tok_lstnew(*toks);
		tok_lstadd_back(&head, new_tok);
		toks++;
	}
	tok_preliminary_type_assigner(head, d);
	tok_secondary_type_assigner(head);
	return (head);
}
