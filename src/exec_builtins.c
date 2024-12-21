/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/18 23:11:46 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

bool	check_for_builtins(t_data *d, t_cmd *cur)
{
	if (input_matches(cur->cmdv[0], "echo"))
		return (skyy_echo(cur), true);
	if (input_matches(cur->cmdv[0], "cd"))
		return (skyy_cd(cur), true);
	if (input_matches(cur->cmdv[0], "pwd"))
		return (skyy_pwd(), true);
	if (input_matches(cur->cmdv[0], "export"))
		return (skyy_export(d, cur->cmdv[1]), true);
	if (input_matches(cur->cmdv[0], "unset"))
		return (skyy_unset(d, cur->cmdv[1]), true);
	if (input_matches(cur->cmdv[0], "env"))
		return (skyy_env(d), true);
	return (false);
}