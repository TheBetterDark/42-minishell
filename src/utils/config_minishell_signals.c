/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_minishell_signals.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:01:31 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 12:04:55 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	config1(struct termios *saved_termios)
{
	struct termios	current;

	tcgetattr(1, saved_termios);
	tcgetattr(1, &current);
	current.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &current);
}

void	config_sigquit(void)
{
	struct sigaction	sigquit;

	sigquit.sa_handler = SIG_IGN;
	sigquit.sa_flags = 0;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	sigint_handle(int signo)
{
	if (signo == SIGINT)
	{
		if (g_signal == HEREDOC_MODE)
		{
			g_signal = HEREDOC_SIGINT;
			ft_putstr_fd("^C\n", STDOUT_FILENO);
		}
		else
		{
			g_signal = MINI_SIGINT;
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	config_sigint(void)
{
	struct sigaction	sigint;

	sigint.sa_handler = sigint_handle;
	sigint.sa_flags = 0;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
}

void	config_minishell_signals(struct termios *saved_termios)
{
	g_signal = NO_SIGNAL;
	config1(saved_termios);
	config_sigquit();
	config_sigint();
}
