/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/21 21:09:34 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	minishell(t_data *d)
{
	while (true)
	{
		d->input = readline("minishell$ ");
		readline_config(d);
		if (!d->input)
			break ;
		d->toks = tokenizer(d);
		d->job = parser(d);
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
