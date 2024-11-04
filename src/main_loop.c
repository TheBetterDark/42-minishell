/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 17:36:29 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	re_init_minishell(t_mini *m)
{
	ft_free_all(m->mem);
	free(m->mem);
	free(m->input);
	init_minishell(m);
	init_signal();
}

static void	process_input_and_execute(t_mini *m)
{
	if (tokenizer(m))
	{
		if (m->t_head->next)
		{
			if (m->t_tail->type == REDIR_IN)
				ft_putstr_fd(SYNTAX_ERR1, 2);
			else
				ft_putstr_fd(SYNTAX_ERR2, 2);
		}
		re_init_minishell(m);
		return ;
	}
	if (parser(m))
	{
		ft_putstr_fd(
			"minishell: parsing error\n", 2);
		re_init_minishell(m);
		return ;
	}
	if (executor(m))
		m->exit_status = 1;
	re_init_minishell(m);
}

void	main_loop(t_mini *m)
{
	while (1)
	{
		config_terminal(m);
		m->input = readline(PROMPT);
		if (!m->input)
		{
			printf("exit\n");
			break ;
		}
		if (m->input[0] == '\0')
		{
			re_init_minishell(m);
			continue ;
		}
		add_history(m->input);
		if (g_signal == SIGINT)
		{
			m->exit_status = 1;
			g_signal = 0;
		}
		process_input_and_execute(m);
	}
}
