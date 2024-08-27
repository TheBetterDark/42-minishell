/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:49:04 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/27 20:52:56 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint(int sig);

t_data	*initialize_shell(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (perror("Error allocating memory"), NULL);
	data->user = getenv("USER");
	if (data->user == NULL)
		return (perror("Error getting USER environment variable"), free(data),
			NULL);
	if (ft_gethostname(data->hostname) == -1)
		return (perror("Error getting hostname"), free(data), NULL);
	if (ft_getcwd(data->cwd, true) == -1)
		return (perror("Error getting current working directory"), free(data),
			NULL);
	return (data);
}

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
