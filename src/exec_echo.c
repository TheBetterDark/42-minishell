/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/18 20:41:31 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

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
//		if (input_matches(*echos, "$?"))
//			ft_putstr_fd(ft_itoa(d->exit_stat), 1);
//		else
		ft_putstr_fd(*echos, 1);
		echos++;
		if (*echos)
			ft_putstr_fd(" ", 1);
	}
	if (!no_endl)
		ft_putstr_fd("\n", 1);
	exit(EXIT_SUCCESS);
}