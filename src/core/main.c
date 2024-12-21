/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/21 21:41:29 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	minishell(t_data *d)
{
	while (true)
	{
		d->input = readline("minishell$ ");
		add_history(d->input);
		if (input_matches(d->input, "history -c"))
			rl_clear_history();
		else if (input_matches(d->input, "exit"))
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		if (!d->input)
			break ;
		d->toks = tokenizer(d);
		d->job = parser(d);
		executor(d);
		free_minishell(d);
	}
}

void	free_minishell(t_data *d)
{
	free(d->input);
	d->cmd_ct = 0;
	tok_lstclear(&d->toks);
	free(d->job);
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
	minishell(d);
	free_data(d);
}
