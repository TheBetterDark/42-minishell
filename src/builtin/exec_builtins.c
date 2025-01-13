/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/13 14:03:34 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Check if the command is a builtin and execute it
*
* @param data The data struct
* @param cmd The current command
*
* @return true if the command is a builtin, false otherwise
*/
bool	check_for_builtins(t_data *data, t_cmd *cmd)
{
	if (input_matches(cmd->cmdv[0], "echo"))
		return (builtin_echo(cmd), true);
	if (input_matches(cmd->cmdv[0], "cd"))
		return (builtin_cd(cmd), true);
	if (input_matches(cmd->cmdv[0], "pwd"))
		return (builtin_pwd(), true);
	if (input_matches(cmd->cmdv[0], "export"))
		return (builtin_export(data, cmd->cmdv[1]), true);
	if (input_matches(cmd->cmdv[0], "unset"))
		return (builtin_unset(data, cmd->cmdv[1]), true);
	if (input_matches(cmd->cmdv[0], "env"))
		return (builtin_env(data), true);
	if (input_matches(cmd->cmdv[0], "exit"))
		exit_minishell(data, EXIT_SUCCESS);
	return (false);
}
