/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/05 08:13:42 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static int	initalize_signals(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		return (perror("Error setting SIGINT handler"), -1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (perror("Error setting SIGQUIT handler"), -1);
	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		return (perror("Error setting SIGTSTP handler"), -1);
	return (0);
}

void	minishell(t_data *d)
{
	while (true)
	{
		d->input = readline("minishell$ ");
		add_history(d->input);
		if (input_matches(d->input, "history -c"))
			rl_clear_history();
		else if (d->input == NULL || ft_strcmp(d->input, "exit") == 0)
			return ;
		if (!d->input)
			continue ;
		d->toks = tokenizer(d);
		d->job = parser(d);
		executor(d);
		free_minishell(d);
	}
}

void	free_minishell(t_data *d)
{
	if (d->input)
	{
		free(d->input);
		d->input = NULL;
	}
	if (d->toks)
	{
		tok_lstclear(&d->toks);
		d->toks = NULL;
	}
	if (d->job)
	{
		cleanup_job(d->job);
		d->job = NULL;
	}
	d->cmd_ct = 0;
	d->input_fd = 0;
	d->output_fd = 1;
	d->r_input_fd = -1;
	d->r_output_fd = -1;
}

int	main(void)
{
	t_data		*d;
	extern char	**environ;

	d = init_data(environ);
	if (initalize_signals() == -1)
		return (free_data(d), EXIT_FAILURE);
	minishell(d);
	free_data(d);
	printf("exit\n");
	return (EXIT_SUCCESS);
}
