/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_type_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 10:10:45 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static void	assign_cmd_toks(t_token *cur, bool *first) //, t_data *d
{
	if (*first && cur->type == ARG)
	{
		cur->type = CMD;
		*first = false;
	}
	else if (cur->type == PIPE)
		*first = true;
}

void	tok_cmd_type_assigner(t_token *head)
{
	t_token	*cur;
	bool	first;

	cur = head;
	first = true;
	while (cur)
	{
		assign_cmd_toks(cur, &first);
		cur = cur->next;
	}
}
