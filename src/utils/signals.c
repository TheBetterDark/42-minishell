/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:52:56 by smoore            #+#    #+#             */
/*   Updated: 2025/02/11 13:23:28 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	init_termios(t_data *data);
void	ignore_sigquit(void);
void	rl_sigint_handler(int signo);
void	normal_sigint_handler(int signo);
void	modify_sigint(int state, t_data *data);

void	init_termios(t_data *data)
{
	struct termios	change;

	tcgetattr(1, &data->saved_termios);
	tcgetattr(1, &change);
	change.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &change);
}

void	ignore_sigquit(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

void	rl_sigint_handler(int signo)
{
	g_signal = signo;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	normal_sigint_handler(int signo)
{
	g_signal = signo;
	ft_putstr_fd("^C\n", STDOUT_FILENO);
}

void	modify_sigint(int state, t_data *data)
{
	struct sigaction	sa;

	(void)data;
	if (state == RL_SIGNAL)
		sa.sa_handler = rl_sigint_handler;
	else if (state == NORMAL_SIGNAL)
		sa.sa_handler = normal_sigint_handler;
	else if (state == IGNORE_SIGNAL)
		sa.sa_handler = SIG_IGN;
	else if (state == CHILD_SIGNAL)
		sa.sa_handler = SIG_IGN;
	else
		printf("There is an error with signit.\n");
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}
