/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:36:43 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 14:27:37 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	cmd_lstclear(t_cmd **head);
void	cmd_lstadd_back(t_cmd **head, t_cmd *new);
t_cmd	*cmd_lstnew(t_token **cur, t_data *data);

void	cmd_lstclear(t_cmd **head)
{
	t_cmd	*cur;
	t_cmd	*next;

	if (*head == NULL)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		ft_str_arr_free(&cur->cmdv);
		if (cur->ins)
			ins_lstclear(&cur->ins);
		if (cur->outs)
			outs_lstclear(&cur->outs);
		free(cur);
		cur = next;
	}
	*head = NULL;
}

void	cmd_lstadd_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*cur;

	if (*head == NULL || !new)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

t_cmd	*cmd_lstnew(t_token **cur, t_data *data)
{
	t_cmd	*new;
	int		size;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	size = find_cmdv_size(*cur);
	new->cmdv = get_cmdv(*cur, size);
	get_io_redirs(&new, *cur, data);
	new->next = NULL;
	while (*cur && (*cur)->type != PIPE)
		*cur = (*cur)->next;
	if (*cur && (*cur)->type == PIPE)
		*cur = (*cur)->next;
	new->pid = -1;
	new->i = data->cmd_ct;
	return (new);
}
