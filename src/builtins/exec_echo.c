/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/05 15:15:20 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

//void	skyy_echo(t_data *d, t_cmd *cur)
void	skyy_echo(t_cmd *cur)
{
	char	**echos;
	bool	no_endl;

	echos = cur->cmdv;
	echos++;
	no_endl = input_matches(*echos, "-n");
	if (no_endl)
		echos++;
	while (*echos)
	{
		ft_putstr_fd(*echos, 1);
		echos++;
		if (*echos)
			ft_putstr_fd(" ", 1);
	}
	if (!no_endl)
		ft_putstr_fd("\n", 1);
	exit(EXIT_SUCCESS);
}
