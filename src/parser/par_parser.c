/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/21 21:41:27 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

t_token	*init_new_cmd(t_cmd **new_cmd, t_token *cur, t_data *d)
{
	int		size;

	size = find_cmdv_size(cur);
	*new_cmd = malloc(sizeof(t_cmd));
	if (!*new_cmd)
		return (NULL);
	(*new_cmd)->cmdv = init_cmdv(cur, size);
	if (!(*new_cmd)->cmdv)
	{
		perror("Cmdv Error");
		return (NULL);
	}
	get_new_cmd_data(*new_cmd, cur, d);
	(*new_cmd)->next = NULL;
	while (cur && cur->type != PIPE)
		cur = cur->next;
	if (cur && cur->type == PIPE)
		cur = cur->next;
	return (cur);
}

void	add_to_job(t_cmd **head_cmd, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (*head_cmd == NULL)
		*head_cmd = new_cmd;
	else
	{
		current = *head_cmd;
		while (current->next != NULL)
			current = current->next;
		current->next = new_cmd;
	}
}

t_cmd	*parser(t_data *d)
{
	t_cmd	*job;
	t_cmd	*new_cmd;
	t_token	*cur;

	job = NULL;
	cur = d->toks;
	while (cur)
	{
		cur = init_new_cmd(&new_cmd, cur, d);
		add_to_job(&job, new_cmd);
	}
	return (job);
}
