/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/05 12:12:00 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	skyy_cd(t_cmd *cur)
{
	if (cur->cmdv[1])
	{
		if (chdir(cur->cmdv[1]) != 0)
			perror("cd");
	}
	else
	{
		if (chdir(getenv("HOME")) != 0)
			perror("cd");
	}
}
