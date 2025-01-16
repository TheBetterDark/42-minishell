/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/16 18:31:39 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Find the size of the command vector
*
* @param cur The current token
*
* @return The size of the command vector
*/
static int	find_cmdv_size(t_token *cur)
{
	t_token	*tmp;
	int		size;

	size = 0;
	tmp = cur;
	while (tmp)
	{
		if (tmp->type == PIPE)
			break ;
		if (tmp->type == CMD || tmp->type == ARG || tmp->type == EXIT_STAT)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

/*
* @brief Find the size of the command vector
*
* @param cur The current token
*
* @return The size of the command vector
*/
static t_cmd	*init_new_cmd(t_token **cur, t_data *data)
{
	t_cmd	*new_cmd;
	int		size;

	size = find_cmdv_size(*cur);
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (handle_error(data, ERR_OUT_OF_MEMORY, EXIT_MEMORY, true), NULL);
	new_cmd->cmdv = init_cmdv(*cur, size, data);
	if (!(new_cmd)->cmdv)
		return (free(new_cmd), NULL);
	get_new_cmd_data(new_cmd, *cur, data);
	(new_cmd)->next = NULL;
	while (*cur && (*cur)->type != PIPE)
		*cur = (*cur)->next;
	if (*cur && (*cur)->type == PIPE)
		*cur = (*cur)->next;
	new_cmd->pid = 0;
	new_cmd->i = data->cmd_ct;
	return (new_cmd);
}

/*
* @brief Add a new command to the job
*
* @param head_cmd The head of the command list
* @param new_cmd The new command to add
*/
static void	add_to_job(t_cmd **head_cmd, t_cmd *new_cmd)
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

/*
* @brief Parse the tokens into commands
*
* @param data The data structure
*
* @return The command list
*/
t_cmd	*parser(t_data *data)
{
	t_cmd	*job;
	t_cmd	*new_cmd;
	t_token	*cur;

	job = NULL;
	cur = data->toks;
	while (cur)
	{
		new_cmd = init_new_cmd(&cur, data);
		if (!new_cmd)
			return (NULL);
		add_to_job(&job, new_cmd);
		data->pipe_ct++;
		data->cmd_ct++;
	}
	return (job);
}
