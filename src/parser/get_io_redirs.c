/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_io_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:37:25 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 14:42:41 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static void	get_ins_redirs(t_cmd **cmd, t_token *toks, t_data *data);
static void	get_outs_redirs(t_cmd **cmd, t_token *toks);
void		get_io_redirs(t_cmd **cmd, t_token *toks, t_data *data);

static void	get_ins_redirs(t_cmd **cmd, t_token *toks, t_data *data)
{
	t_ins	*in_new;

	in_new = NULL;
	while (toks && toks->type != PIPE)
	{
		if (toks->type == FN_READ || toks->type == DELIM)
		{
			in_new = ins_lstnew(toks, data);
			if (!in_new)
			{
				ins_lstclear(&(*cmd)->ins);
				return ;
			}
			ins_lstadd_back(&(*cmd)->ins, in_new);
		}
		toks = toks->next;
	}
}

static void	get_outs_redirs(t_cmd **cmd, t_token *toks)
{
	t_outs	*out_new;

	out_new = NULL;
	while (toks && toks->type != PIPE)
	{
		if (toks->type == FN_TRUNC || toks->type == FN_APPEND)
		{
			out_new = outs_lstnew(toks);
			if (!out_new)
			{
				outs_lstclear(&(*cmd)->outs);
				return ;
			}
			outs_lstadd_back(&(*cmd)->outs, out_new);
		}
		toks = toks->next;
	}
}

void	get_io_redirs(t_cmd **cmd, t_token *toks, t_data *data)
{
	(*cmd)->ins = NULL;
	(*cmd)->outs = NULL;
	get_ins_redirs(cmd, toks, data);
	get_outs_redirs(cmd, toks);
}
