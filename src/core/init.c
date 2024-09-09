/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:49:04 by muabdi            #+#    #+#             */
/*   Updated: 2024/09/09 19:53:39 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	handle_sigint(int sig);

/*
* @brief Initialize the shell
*
* @return t_data* The shell data structure
*/
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
		return (free(data), NULL);
	if (ft_getcwd(data->cwd, true) == -1)
		return (free(data), NULL);
	data->input = NULL;
	data->commands = NULL;
	data->out_file = NULL;
	data->in_file = NULL;
	data->err_file = NULL;
	return (data);
}

/*
* @brief Initialize signal handlers
*
* @return int 0 on success, -1 on error
*/
// int	initalize_signals(void)
// {
// 	if (signal(SIGINT, handle_sigint) == SIG_ERR)
// 		return (perror("Error setting SIGINT handler"), -1);
// 	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
// 		return (perror("Error setting SIGQUIT handler"), -1);
// 	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
// 		return (perror("Error setting SIGTSTP handler"), -1);
// 	return (0);
// }

/*
* @brief Handle the SIGINT signal
*
* @param sig The signal number
*/
// static void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }
