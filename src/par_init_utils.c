/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/21 21:10:06 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

int	find_cmdv_size(t_token *cur)
{
	t_token	*cur_cur;
	int		size;

	size = 0;
	cur_cur = cur;
	while (cur_cur && (cur_cur->type == CMD || cur_cur->type == ARG))
	{
		size++;
		cur_cur = cur_cur->next;
	}
	return (size);
}

void	set_new_cmd_nulls(t_cmd *new_cmd)
{
	new_cmd->append_fn = NULL;
	new_cmd->open_fn = NULL;
	new_cmd->input_fn = NULL;
	new_cmd->eof = NULL;
	new_cmd->e_len = 0;
	new_cmd->next = NULL;
}

void	get_new_cmd_data(t_cmd *new_cmd, t_token *cur, t_data *d)
{
	set_new_cmd_nulls(new_cmd);
	while (cur)
	{
		if (cur->type == APPEND_FILE)
			new_cmd->append_fn = cur->cont;
		if (cur->type == OUT_FILE)
			new_cmd->open_fn = cur->cont;
		if (cur->type == IN_FILE)
			new_cmd->input_fn = cur->cont;
		if (cur->type == DELIM)
		{
			new_cmd->eof = cur->cont;
			new_cmd->e_len = ft_strlen(cur->cont);
		}
		if (cur->type == EXIT_STAT)
		{
			cur->cont = ft_itoa(d->exit_stat);
			printf("->> %s\n", cur->cont);
		}
		cur = cur->next;
	}
}
