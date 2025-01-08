/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_type_assigner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/08 18:48:01 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static void	assign_redir_toks(t_token *cur)
{
	if (input_matches(cur->cont, "|"))
		cur->type = PIPE;
	else if (input_matches(cur->cont, "<"))
		cur->type = RDR_IN;
	else if (input_matches(cur->cont, "<<"))
		cur->type = RDR_HEREDOC;
	else if (input_matches(cur->cont, ">"))
		cur->type = RDR_OUT;
	else if (input_matches(cur->cont, ">>"))
		cur->type = RDR_APPEND;
	else
		cur->type = ARG;
}

void	tok_redir_operator_type_assigner(t_token *head)
{
	t_token	*cur;
	bool	first;

	cur = head;
	first = true;
	while (cur)
	{
		assign_redir_toks(cur);
		cur = cur->next;
	}
}

static void	assign_redir_file_toks(t_token *cur)
{
	if (cur->prev && cur->type == ARG && cur->prev->type == RDR_IN)
		cur->type = IN_FILE;
	else if (cur->prev && cur->type == ARG && cur->prev->type == RDR_HEREDOC)
		cur->type = DELIM;
	else if (cur->prev && cur->type == ARG && cur->prev->type == RDR_OUT)
		cur->type = OUT_FILE;
	else if (cur->prev && cur->type == ARG && cur->prev->type == RDR_APPEND)
		cur->type = APPEND_FILE;
	else if (input_matches(cur->cont, "$?"))
		cur->type = EXIT_STAT;
}

void	tok_redir_file_type_assigner(t_token *head)
{
	t_token	*cur;

	cur = head;
	while (cur)
	{
		if (cur->type >= RDR_IN && cur->type <= ARG)
			assign_redir_file_toks(cur);
		cur = cur->next;
	}
}
