/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_tok_type_assigner.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/16 13:18:48 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	assign_one_type(t_token *tok, int *type)
{
	if(is_valid_cmd(tok->cont))	
		*type = CMD;	
	else
		*type = CMD_ERR;
}

void	assign_multiple_type(char *tok, int *type)
{
	int	len;

	len = ft_strlen(tok);
	if (ft_memcmp(tok, "|", len) == 0)
		*type = PIPE;
	else if (ft_memcmp(tok, "<", len) == 0)
		*type = RDR_IN;
	else if (ft_memcmp(tok, ">", len) == 0)
		*type = RDR_OUT;
	else if (ft_memcmp(tok, ">>", len) == 0)
		*type = APPEND;
	else if (is_fd(tok))
		*type = FD;
	else if (is_delim(tok))
		*type = DELIMS;
	else if (is_filename(tok))
		*type = FILENAME;
	else if (is_cmd(tok))
		*type = CMD;
	else
		*type = ARG;
}

void	tok_type_assigner(t_token *head)
{
	t_token	*current;

	current = head;
	if ((tok_lstsize(current)) == 1)
			assign_one_type(head, &current->type);
	else
	{
		while (current != NULL)
		{
			assign_multiple_type(current->cont, &current->type);
			current = current->next;
		}
	}
}
