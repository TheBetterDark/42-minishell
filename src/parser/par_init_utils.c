/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/23 18:12:20 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Set the new command to NULL
*
* @param new_cmd The new command
*/
static void	set_new_cmd_nulls(t_cmd *new_cmd)
{
	new_cmd->ins = NULL;
	new_cmd->outs = NULL;
	new_cmd->pid = -1;
	new_cmd->i = 0;
	new_cmd->next = NULL;
}

/*
* @brief strdup the content of the token
*
* @param cont The content of the token
* @param rdr The redirection operator
*
* @return The new string
*/
static char	*strdup_redir(char *cont, char *rdr)
{
	char	*trim;

	trim = ft_strtrim(cont, rdr);
	free(cont);
	return (trim);
}

/*
* @brief Handle the filename
*
* @param file_name The file name
* @param cur The current token
* @param type The type of the token
* @param rdr The redirection operator
*/
char	*handle_filename(t_token *cur, int type, char *rdr)
{
	char	*filename;
	char	c;

	c = rdr[0];
	filename = NULL;
	if (cur->type == type)
	{
		if (cur->cont[0] == c)
			filename = strdup_redir(cur->cont, rdr);
		else
			filename = ft_strdup(cur->cont);
	}
	return (filename);
}

/*
* @brief Get the new command data
*
* @param new_cmd The new command
* @param cur The current token
* @param data The data structure
*/
void	get_new_cmd_data(t_cmd *new_cmd, t_token *cur, t_data *data)
{
	t_in	*head_in;
	t_out	*head_out;

	head_in = NULL;
	head_out = NULL;
	set_new_cmd_nulls(new_cmd);
	while (cur)
	{
		if (cur->type == PIPE)
			break ;
		if (cur->type == EXIT_STAT)
			cur->cont = ft_itoa(data->exit_stat);
		if (cur->type == IN_FILE || cur->type == DELIM)
			new_cmd->ins = init_in_redirections(&head_in, cur);
		if (cur->type == OUT_FILE || cur->type == APPEND_FILE)
			new_cmd->outs = init_out_redirections(&head_out, cur);
		cur = cur->next;
	}
}
