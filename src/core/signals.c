/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:51:08 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/26 23:02:29 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint(int sig);

int	initalize_signals(void)

{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		return (perror("Error setting SIGINT handler"), -1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (perror("Error setting SIGQUIT handler"), -1);
	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		return (perror("Error setting SIGTSTP handler"), -1);
	return (0);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
