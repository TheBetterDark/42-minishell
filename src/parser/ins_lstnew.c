/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:37:30 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 14:23:09 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	ins_lstclear(t_ins **head);
void	ins_lstadd_back(t_ins **head, t_ins *new);
t_ins	*ins_lstnew(t_token *cur, t_data *data);

void	ins_lstclear(t_ins **head)
{
	t_ins	*cur;
	t_ins	*next;

	if (*head == NULL)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		if (cur->eof)
		{
			free(cur->eof);
			unlink(cur->read_fn);
		}
		cur->eof = NULL;
		if (cur->read_fn)
			free(cur->read_fn);
		cur->read_fn = NULL;
		free(cur);
		cur = next;
	}
	*head = NULL;
}

void	ins_lstadd_back(t_ins **head, t_ins *new)
{
	t_ins	*cur;

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

static char	*get_heredoc_filename(int heredoc_ct)
{
	char	*num;
	char	*join;

	num = ft_itoa(heredoc_ct);
	join = ft_strjoin("h3gh34HG_", num);
	free(num);
	return (join);
}

static void	set_default_values(t_ins *new)
{
	new->eof = NULL;
	new->eof_len = 0;
	new->eof_quoted = false;
	new->fd = -1;
	new->read_fn = NULL;
	new->next = NULL;
}

t_ins	*ins_lstnew(t_token *cur, t_data *data)
{
	t_ins	*new;

	new = malloc(sizeof(t_ins));
	if (!new)
		return (NULL);
	set_default_values(new);
	if (cur->type == DELIM)
	{
		new->read_fn = get_heredoc_filename(data->heredoc_ct++);
		new->eof = ft_strjoin(cur->str, "\n");
		new->eof_len = ft_strlen(new->eof);
		if (has_quotes(new->eof))
			new->eof_quoted = true;
	}
	else if (cur->type == FN_READ)
		new->read_fn = ft_strdup(cur->str);
	return (new);
}
