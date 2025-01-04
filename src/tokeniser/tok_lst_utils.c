/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/04 18:26:03 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

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
