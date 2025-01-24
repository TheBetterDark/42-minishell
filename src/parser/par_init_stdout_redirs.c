/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_init_stdout_redirs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/24 17:43:14 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	clear_out_list(t_out **head)
{
	t_out	*cur;
	t_out	*temp;

	if (*head == NULL)
		return ;
	cur = *head;
	while (cur != NULL)
	{
		temp = cur->next;
		if (cur->truc_fn)
			free(cur->truc_fn);
		cur->truc_fn = NULL;
		if (cur->append_fn)
			free(cur->append_fn);
		cur->append_fn = NULL;
		free(cur);
		cur = temp;
	}
	*head = NULL;
}

void	add_out_redir(t_out **head, t_out *new)
{
	t_out	*cur;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
}

t_out	*new_out_redir(t_token *cur)
{
	t_out	*new_out;

	new_out = (t_out *)malloc(sizeof(t_out));
	if (!new_out)
		return (NULL);
	new_out->truc_fn = NULL;
	new_out->append_fn = NULL;
	new_out->next = NULL;
	if (cur->type == APPEND_FILE)
		new_out->append_fn = handle_filename(cur, APPEND_FILE, ">>");
	else if (cur->type == OUT_FILE)
		new_out->truc_fn = handle_filename(cur, OUT_FILE, ">");
	return (new_out);
}

t_out	*init_out_redirections(t_out **head, t_token *cur)
{
	t_out	*new;

	if (cur->type == PIPE)
		return (*head);
	new = new_out_redir(cur);
	if (!new)
		return (clear_out_list(head), NULL);
	add_out_redir(head, new);
	return (*head);
}
