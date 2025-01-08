/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/08 20:00:32 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

int	find_cmdv_size(t_token *cur)
{
	t_token	*tmp;
	int		size;

	size = 0;
	tmp = cur;
	while (tmp)
	{
		if (tmp->type == CMD || tmp->type == ARG
			|| tmp->type == EXIT_STAT)
			size++;
		tmp = tmp->next;
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

static char	*strdup_redir(char *cont, char *rdr)
{
	char	*trim;

	trim = ft_strtrim(cont, rdr);
	free(cont);
	return (trim);
}

static void	handle_filename(char **file_name, t_token *cur, int type, char *rdr)
{
	char c;

	c = rdr[0];
	if (cur->type == type)
	{
		if (cur->cont[0] == c)
			*file_name = strdup_redir(cur->cont, rdr);
		else
			*file_name = ft_strdup(cur->cont);
	}
}

void	get_new_cmd_data(t_cmd *new_cmd, t_token *cur, t_data *d)
{
	set_new_cmd_nulls(new_cmd);
	while (cur)
	{
		handle_filename(&new_cmd->append_fn, cur, APPEND_FILE, ">>");
		handle_filename(&new_cmd->open_fn, cur, OUT_FILE, ">");
		handle_filename(&new_cmd->input_fn, cur, IN_FILE, "<");
		if (cur->type == DELIM)
		{
			new_cmd->eof = cur->cont;
			new_cmd->e_len = ft_strlen(cur->cont);
		}
		if (cur->type == EXIT_STAT)
		{
			cur->cont = ft_itoa(d->exit_stat);
		}
		cur = cur->next;
	}
}
