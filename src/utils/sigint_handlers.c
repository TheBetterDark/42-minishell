/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:52:56 by smoore            #+#    #+#             */
/*   Updated: 2025/02/12 19:03:53 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	rl_sigint_handler(int signo);
void	normal_sigint_handler(int signo);
void	child_sigint_handler(int signo);
void	heredoc_sigint_handler(int signo);
void	modify_sigint(int state, t_data *data);

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
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	child_sigint_handler(int signo)
{
	g_signal = signo;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	heredoc_sigint_handler(int signo)
{
	g_signal = signo;
	ft_putstr_fd("\n", STDOUT_FILENO);
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
	{
		tcsetattr(1, TCSAFLUSH, &data->saved_termios);
		sa.sa_handler = child_sigint_handler;
	}
	else if (state == HEREDOC_SIGNAL)
		sa.sa_handler = heredoc_sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}
