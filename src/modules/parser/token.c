/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:59:05 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/30 10:39:43 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_token	*token_new(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	token_append(t_token **tokens, t_token *new)
{
	t_list	*last;

	if (!new)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	token_cleanup(t_token **tokens)
{
	if (!tokens || !*tokens)
		return ;
	if ((*tokens)->next)
		token_cleanup(&(*tokens)->next);
	if ((*tokens)->value)
		free((*tokens)->value);
	free(*tokens);
	*tokens = NULL;
}
