/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termios.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:52:56 by smoore            #+#    #+#             */
/*   Updated: 2025/02/12 19:28:20 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	child_sigquit_handler(int signo);
void	modify_sigquit(int state);
void	init_termios(t_data *data);

void	parent_sigquit_handler(int signo)
{
	g_signal = signo;
	ft_putstr_fd("Quit\n", STDOUT_FILENO);
}

void	child_sigquit_handler(int signo)
{
	g_signal = signo;
	exit(EXIT_FAILURE);
}

void	modify_sigquit(int state)
{
	struct sigaction	sa;

	if (state == NORMAL_SIGNAL)
		sa.sa_handler = SIG_IGN;
	else if (state == CHILD_SIGNAL)
		sa.sa_handler = child_sigquit_handler;
	else if (state == PARENT_SIGNAL)
		sa.sa_handler = parent_sigquit_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

void	init_termios(t_data *data)
{
	struct termios	change;

	tcgetattr(1, &data->saved_termios);
	tcgetattr(1, &change);
	change.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &change);
}
