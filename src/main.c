/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/20 14:17:55 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	minishell(t_data *d)
{
	while (1)
	{
		d->input = readline("minishell$ ");
		readline_config(d);
		if (!d->input)
			break ;
		d->toks = tokenizer(d);
//		print_toks(d);
		d->job = parser(d);
//		print_job(d->job);
		executor(d);
		free_minishell(d);
	}
}

int	main(void)
{
	t_data		*d;
	extern char	**environ;

	d = init_data(environ);
	minishell(d);
	free_data(d);
}
