/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_init_stdin_redirs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/23 18:07:16 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	clear_in_list(t_in **head)
{
	t_in	*cur;
	t_in	*temp;

	if (*head == NULL)
		return ;
	cur = *head;
	while (cur != NULL)
	{
		temp = cur->next;
		if (cur->eof)
			free(cur->eof);
		if (cur->read_fn)
			free(cur->read_fn);
		free(cur);
		cur = temp;
	}
	*head = NULL;
}

void	add_in_redir(t_in **head, t_in *new)
{
	t_in *cur;

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

t_in	*new_in_redir(t_token *cur)
{
	t_in *new_in;

	new_in = malloc(sizeof(t_in));
	if (!new_in)
		return (NULL);
	new_in->eof = NULL;
	new_in->eof_len = 0;
	new_in->pipe_fds[0] = -1;
	new_in->pipe_fds[1] = -1;
	new_in->pid = -1;
	new_in->heredoc_fd = -1;
	new_in->read_fn = NULL;
	new_in->next = NULL;
	if (cur->type == DELIM)
	{
		new_in->eof = ft_strdup(cur->cont);
		new_in->eof_len = ft_strlen(cur->cont);
	}
	else if (cur->type == IN_FILE)	
		new_in->read_fn = handle_filename(cur, IN_FILE, "<");
	return (new_in);
}

t_in	*init_in_redirections(t_in **head, t_token *cur)
{
	t_in	*new;

	if (cur->type == PIPE)
		return (*head);
	new = new_in_redir(cur);
	if (!new)
		return (clear_in_list(head), NULL);
	add_in_redir(head, new);
	return (*head);
}
