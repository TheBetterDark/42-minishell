/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/13 17:15:27 by smoore           ###   ########.fr       */
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
	new_cmd->append_fn = NULL;
	new_cmd->open_fn = NULL;
	new_cmd->input_fn = NULL;
	new_cmd->eof = NULL;
	new_cmd->e_len = 0;
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
static void	handle_filename(char **file_name, t_token *cur, int type, char *rdr)
{
	char	c;

	c = rdr[0];
	if (cur->type == type)
	{
		if (cur->cont[0] == c)
			*file_name = strdup_redir(cur->cont, rdr);
		else
			*file_name = ft_strdup(cur->cont);
	}
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
			cur->cont = ft_itoa(data->exit_stat);
		}
		cur = cur->next;
	}
}
