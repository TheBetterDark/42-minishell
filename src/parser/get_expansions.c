/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:37:06 by smoore            #+#    #+#             */
/*   Updated: 2025/02/12 17:21:48 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	expand_ins(t_ins **in, t_data *data);
void	expand_outs(t_outs **outs, t_data *data);
char	*swap_processed_str(char *str, t_data *data);
void	expand_cur_cmds(t_cmd *cmd, t_data *data);
void	get_expansions(t_cmd **cmds, t_data *data);

void	expand_ins(t_ins **ins, t_data *data)
{
	t_ins	*in_cur;

	in_cur = *ins;
	while (in_cur)
	{
		if (in_cur->eof)
			in_cur->eof = swap_processed_str(in_cur->eof, data);
		else if (in_cur->read_fn)
			in_cur->read_fn = swap_processed_str(in_cur->read_fn, data);
		in_cur = in_cur->next;
	}
}

void	expand_outs(t_outs **outs, t_data *data)
{
	t_outs	*out_cur;

	out_cur = *outs;
	while (out_cur)
	{
		if (out_cur->trunc_fn)
			out_cur->trunc_fn = swap_processed_str(out_cur->trunc_fn, data);
		else if (out_cur->append_fn)
			out_cur->append_fn = swap_processed_str(out_cur->append_fn, data);
		out_cur = out_cur->next;
	}
}

char	*swap_processed_str(char *str, t_data *data)
{
	char	*dup;

	if (word_match(str, "$") || word_match(str, "$$"))
		return (str);
	dup = process_str(str, data);
	free(str);
	return (dup);
}

void	expand_cur_cmds(t_cmd *cmd, t_data *data)
{
	char	**cmdv;
	char	**head;
	char	*tmp;

	cmdv = cmd->cmdv;
	while (*cmdv)
	{
		*cmdv = swap_processed_str(*cmdv, data);
		cmdv++;
	}
	head = cmd->cmdv;
	tmp = cmd->cmdv[0];
	if (!is_builtin_cmd_child(head[0]))
	{
		cmd->cmdv[0] = add_path_cmdv0(&head[0], data);
		free(tmp);
	}
	if (cmd->ins)
		expand_ins(&cmd->ins, data);
	if (cmd->outs)
		expand_outs(&cmd->outs, data);
}

void	get_expansions(t_cmd **cmds, t_data *data)
{
	t_cmd	*cur;

	if (!(*cmds) && !cmds)
		return ;
	cur = *cmds;
	while (cur)
	{
		expand_cur_cmds(cur, data);
		cur = cur->next;
	}
}
