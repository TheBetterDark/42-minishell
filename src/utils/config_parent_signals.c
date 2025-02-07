/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parent_signals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:02:02 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 12:04:32 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	parent_sigint_handl3(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("^C\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	config_parent_sigint(void)
{
	struct sigaction	sigint;

	g_signal = 1;
	sigint.sa_handler = parent_sigint_handl3;
	sigint.sa_flags = 0;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
}

void	config_parent_signals(void)
{
	config_parent_sigint();
	config_sigquit();
}
