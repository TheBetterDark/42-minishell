/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/02/10 20:14:34 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	builtin_echo(t_cmd *cmd);

/*
* @brief Print the arguments to the standard output
*
* @param cmd The current command
*/

void	builtin_echo(t_cmd *cmd)
{
	char	**echos;
	bool	no_endl;

	no_endl = false;
	echos = cmd->cmdv;
	echos++;
	if (*echos)
		no_endl = word_match(*echos, "-n");
	if (no_endl)
		echos++;
	while (*echos)
	{
		ft_putstr_fd(*echos, STDOUT_FILENO);
		echos++;
		if (*echos)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!no_endl)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
