/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_type_assigner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/21 18:34:02 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

/*
bool	is_(t_token *cur)
{
		return (true);
	return (false);
}
*/

// static void	select_type(t_data *d, t_token *cur, int first)
// {
// 	if (is_cmd(cur, first))
// 	{
// 		cur->type = CMD;
// 		d->cmd_ct++;
// 		first = false;
// 	}
// 	else if (input_matches(cur->cont, "|"))
// 		cur->type = PIPE;
// 	else if (input_matches(cur->cont, "<"))
// 		cur->type = RDR_IN;
// 	else if (input_matches(cur->cont, "<<"))
// 		cur->type = RDR_HEREDOC;
// 	else if (input_matches(cur->cont, ">"))
// 		cur->type = RDR_OUT;
// 	else if (input_matches(cur->cont, ">>"))
// 		cur->type = RDR_APPEND;
// 	else
// 		cur->type = ARG;
// }

void	tok_preliminary_type_assigner(t_token *head, t_data *d)
{
	t_token	*cur;
	bool	first;

	cur = head;
	first = true;
	while (cur)
	{
		if (is_cmd(cur, first))
		{
			cur->type = CMD;
			d->cmd_ct++;
			first = false;
		}
		else if (input_matches(cur->cont, "|"))
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
		cur = cur->next;
	}
}

static void	double_check_arg(t_token *cur)
{
	// ls > out
	if (cur->prev->type == RDR_IN)
		cur->type = IN_FILE;
	else if (cur->prev->type == RDR_HEREDOC)
		cur->type = DELIM; // does prev work
	else if (cur->prev->type == RDR_OUT)
		cur->type = OUT_FILE;
	else if (cur->prev->type == RDR_APPEND)
		cur->type = APPEND_FILE;
	else if (input_matches(cur->cont, "$?"))
		cur->type = EXIT_STAT;
}

void	tok_secondary_type_assigner(t_token *head)
{
	t_token	*cur;

	cur = head;
	while (cur)
	{
		if (cur->type == ARG)
			double_check_arg(cur);
		cur = cur->next;
	}
}
