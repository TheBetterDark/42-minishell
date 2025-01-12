/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 15:39:34 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

t_cmd	*init_new_cmd(t_token **cur, t_data *d)
{
	t_cmd	*new_cmd;
	int		size;

	size = find_cmdv_size(*cur);
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	(new_cmd)->cmdv = init_cmdv(*cur, size, d);
	if (!(new_cmd)->cmdv)
	{
		free(new_cmd);
		return (NULL);
	}
	get_new_cmd_data(new_cmd, *cur, d);
	(new_cmd)->next = NULL;
	while (*cur && (*cur)->type != PIPE)
		*cur = (*cur)->next;
	if (*cur && (*cur)->type == PIPE)
		*cur = (*cur)->next;
	new_cmd->pid = 0;
	return (new_cmd);
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

void	cleanup_job(t_cmd *job)
{
	t_cmd	*tmp;

	while (job)
	{
		tmp = job;
		job = job->next;
		ft_free_str_arr(&tmp->cmdv);
		if (tmp->open_fn)
			free(tmp->open_fn);
		tmp->open_fn = NULL;
		if (tmp->append_fn)
			free(tmp->append_fn);
		tmp->append_fn = NULL;
		if (tmp->input_fn)
			free(tmp->input_fn);
		tmp->input_fn = NULL;
		free(tmp);
		tmp = NULL;
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
		new_cmd = init_new_cmd(&cur, d);
		add_to_job(&job, new_cmd);
	}
	return (job);
}
