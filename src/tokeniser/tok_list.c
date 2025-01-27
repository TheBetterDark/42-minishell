/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/27 18:11:31 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Creates a new token
*
* @param word The word to be stored in the token
*
* @return The new token
*/
t_token	*tok_lstnew(char *word, t_data *data)
{
	t_token	*new_tok;

	new_tok = (t_token *)malloc(sizeof(t_token));
	if (!new_tok)
		return (NULL);
	new_tok->cont = process_tok_cont(word, data);
	new_tok->next = NULL;
	new_tok->prev = NULL;
	return (new_tok);
}

/*
* @brief Adds a new token to the end of the list
*
* @param head The head of the list
* @param new The new token
*/
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

/*
* @brief Counts the number of tokens in the list
*
* @param tok The head of the list
*
* @return The number of tokens in the list
*/
int	tok_lstsize(t_token *tok)
{
	int	i;

	i = 0;
	while (tok != NULL)
	{
		i++;
		tok = tok->next;
	}
	return (i);
}

/*
* @brief Returns the last token in the list
*
* @param tok The head of the list
*
* @return The last token in the list
*/
t_token	*tok_lstlast(t_token *tok)
{
	if (tok == NULL)
		return (0);
	while (tok)
	{
		if (tok->next == NULL)
			return (tok);
		tok = tok->next;
	}
	return (tok);
}

/*
* @brief Clears the list of tokens
*
* @param tok The head of the list
*/
void	tok_lstclear(t_token **tok)
{
	t_token	*current;
	t_token	*temp;

	if (*tok == NULL)
		return ;
	current = *tok;
	while (current != NULL)
	{
		temp = current->next;
		free(current->cont);
		free(current);
		current = temp;
	}
	*tok = NULL;
}
