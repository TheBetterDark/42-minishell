/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:52:56 by smoore            #+#    #+#             */
/*   Updated: 2025/02/19 13:29:20 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

volatile sig_atomic_t	g_signal;

char		*read_command_line(t_data *data);
void		run_minishell(t_data *data);

char	*read_command_line(t_data *data)
{
	char	*input;
	char	*trim;

	modify_sigint(RL_SIGNAL, data);
	modify_sigquit(NORMAL_SIGNAL);
	input = readline("minishell$ ");
	if (input)
		add_history(input);
	if (!input)
		return (NULL);
	modify_sigint(NORMAL_SIGNAL, data);
	trim = ft_strtrim(input, " \t");
	free(input);
	input = complete_quoted_input(trim);
	return (input);
}

void	run_minishell(t_data *data)
{
	while (data)
	{
		free_minishell(data);
		data->input = read_command_line(data);
		if (g_signal)
			g_signal = NO_SIGNAL;
		if (!data->input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (word_match(data->input, "history -c"))
		{
			rl_clear_history();
			continue ;
		}
		tokenize(data);
		if (data->token_syntax_error == true)
			continue ;
		parse(data);
		execute(data);
	}
}

int	main(void)
{
	t_data	*data;

	if (!isatty(STDIN_FILENO) || !isatty(STDERR_FILENO))
	{
		ft_putstr_fd("minishell: not a terminal", STDERR_FILENO);
		return (1);
	}
	data = initialize_minishell();
	run_minishell(data);
	ft_str_arr_free(&data->env);
	free_minishell(data);
	if (data->pwd)
		free(data->pwd);
	free(data);
	return (0);
}
