/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 15:48:02 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

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

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	minishell(t_data *d)
{
	while (true)
	{
		if (initalize_signals() == -1)
			return ;
		d->input = readline("minishell$ ");
		if (!d->input || ft_strcmp(d->input, "exit") == 0)
			return ;
		if (d->input[0] != '\0')
			add_history(d->input);
		if (input_matches(d->input, "history -c"))
			rl_clear_history();
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
		tok_lstclear(&d->toks);
	if (d->job)
	{
		cleanup_job(d->job);
		d->job = NULL;
	}
	d->cmd_ct = 0;
	d->r_input_fd = -1;
	d->r_output_fd = -1;
}

int	main(void)
{
	t_data		*d;
	extern char	**environ;

	d = init_data(environ);
	minishell(d);
	free_data(d);
	printf("exit\n");
	return (EXIT_SUCCESS);
}
