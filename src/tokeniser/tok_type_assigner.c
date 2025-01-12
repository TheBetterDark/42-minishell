/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_type_assigner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 20:16:04 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Assigns the type of the redirection operator
*
* @param cur The current token
*/
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

/*
* @brief Assigns the type of the redirection file
*
* @param cur The current token
*/
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

/*
* @brief Assigns the type of the redirection operator
*
* @param head The head of the token list
*/
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

/*
* @brief Assigns the type of the redirection file
*
* @param head The head of the token list
*/
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

/*
* @brief Assigns the type of the redirection operator
*
* @param head The head of the token list
*/
void	tok_cmd_type_assigner(t_token *head)
{
	t_token	*cur;
	bool	first;

	cur = head;
	first = true;
	while (cur)
	{
		if (first && cur->type == ARG)
		{
			cur->type = CMD;
			first = false;
		}
		else if (cur->type == PIPE)
			first = true;
		cur = cur->next;
	}
}
