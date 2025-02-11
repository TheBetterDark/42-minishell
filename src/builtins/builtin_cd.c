/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 18:51:55 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	builtin_cd(t_data *data, t_cmd *cmd)
{
	if (cmd->cmdv[1])
	{
		if (chdir(cmd->cmdv[1]) != 0)
			perror("cd");
	}
	else
	{
		if (chdir(getenv("HOME")) != 0)
			perror("cd");
	}
	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
}
