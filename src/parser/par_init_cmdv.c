/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_init_cmdv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/13 13:12:57 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Get the paths from the environment variable
*
* @param data The data struct
*
* @return The paths
*/
static char	**get_paths(t_data *data)
{
	char	*path;
	char	**paths;

	path = ft_str_arr_has((const char **)data->env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (handle_error(data, ERR_OUT_OF_MEMORY, EXIT_MEMORY, true), NULL);
	return (paths);
}

/*
* @brief Add the path to the command
*
* @param data The data struct
* @param cmd_name The command name
*
* @return The command with the path
*/
static char	*add_path_to_cmdv0(t_data *data, char *cmd_name)
{
	char	**paths;
	char	**tmp;
	char	*target_path;
	char	*cmdv0;

	paths = get_paths(data);
	if (!paths)
		return (NULL);
	tmp = paths;
	while (*tmp)
	{
		target_path = search_paths(*tmp, cmd_name);
		if (target_path)
		{
			cmdv0 = target_path;
			ft_free_str_arr(&paths);
			return (cmdv0);
		}
		tmp++;
	}
	ft_free_str_arr(&paths);
	return (NULL);
}

/*
* @brief Handles the first command in the command vector
*
* @param cur The current token
* @param data The data struct
*
* @return The command name
*/
// TODO: Do this in the executor
static char	*handle_first_command(t_token *cur, t_data *data)
{
	char	*cmd_name;

	if (is_builtin_command(cur->cont))
		cmd_name = ft_strdup(cur->cont);
	else
	{
		if (access(cur->cont, F_OK | X_OK) == 0)
		{
			cmd_name = ft_strdup(cur->cont);
			if (!cmd_name)
				return (handle_error(data,
						ERR_OUT_OF_MEMORY, EXIT_MEMORY, true), NULL);
		}
		else
			cmd_name = add_path_to_cmdv0(data, cur->cont);
		if (!cmd_name)
			return (handle_error(data, ERR_CMD_NOT_FOUND, 127, false), NULL);
	}
	return (cmd_name);
}

/*
* @brief Duplicates the command
*
* @param cur The current token
* @param is_first If the command is the first command
* @param data The data struct
*
* @return The duplicated command
*/
static char	*duplicate_command(t_token *cur, int is_first, t_data *data)
{
	char	*cmd_name;

	if (is_first == 0)
		cmd_name = handle_first_command(cur, data);
	else
	{
		if (cur->type == ARG && cur->cont[0] == '\"')
			cmd_name = dup_double_quotes(ft_strtrim(cur->cont, "\""), data);
		else if (cur->type == ARG && cur->cont[0] == '\'')
			cmd_name = ft_strdup(ft_strtrim(cur->cont, "\'"));
		else if (cur->type == EXIT_STAT)
			cmd_name = ft_itoa(data->exit_stat);
		else
			cmd_name = ft_strdup(cur->cont);
		if (!cmd_name)
			return (handle_error(data, ERR_OUT_OF_MEMORY, EXIT_MEMORY, true),
				NULL);
	}
	return (cmd_name);
}

/*
* @brief Initializes the command vector
*
* @param cur The current token
* @param size The size of the command vector
* @param data The data struct
*
* @return The command vector
*/
char	**init_cmdv(t_token *cur, int size, t_data *data)
{
	char	**cmdv;
	int		i;

	cmdv = malloc(sizeof(char *) * (size + 1));
	if (!cmdv)
		return (handle_error(data, ERR_OUT_OF_MEMORY, EXIT_MEMORY, true), NULL);
	i = 0;
	while (i < size && cur)
	{
		if ((cur->type == CMD || cur->type == ARG
				|| cur->type == EXIT_STAT) && cur->type != PIPE)
		{
			cmdv[i] = duplicate_command(cur, i, data);
			if (!cmdv[i])
			{
				while (i > 0)
					free(cmdv[--i]);
				return (free(cmdv), NULL);
			}
			i++;
		}
		cur = cur->next;
	}
	cmdv[i] = NULL;
	return (cmdv);
}
