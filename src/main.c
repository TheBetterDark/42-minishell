/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:52:56 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 11:56:50 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

volatile sig_atomic_t	g_signal;

t_data	*initialize_minishell(void);
void	free_minishell(t_data *data);
char	*read_command_line(void);
void	run_minishell(t_data *data);

t_data	*initialize_minishell(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->input = NULL;
	data->toks = NULL;
	data->cmds = NULL;
	data->cmd_ct = 0;
	data->pipe_ct = 0;
	data->heredoc_ct = 0;
	data->env = ft_str_arr_dup((const char **)__environ);
	data->read_fd = -1;
	data->write_fd = -1;
	return (data);
}

void	free_minishell(t_data *data)
{
	if (data)
	{
		if (data->input)
			free(data->input);
		if (data->toks)
			tok_lstclear(&data->toks);
		if (data->cmds && data->pipe_ct)
			free_pipes(data, data->pipe_ct);
		if (data->cmds)
			cmd_lstclear(&data->cmds);
		if (data->read_fd != -1)
		{
			close(data->read_fd);
			data->read_fd = -1;
		}
		if (data->write_fd != -1)
		{
			close(data->write_fd);
			data->write_fd = -1;
		}
		data->cmd_ct = 0;
		data->pipe_ct = 0;
		data->heredoc_ct = 0;
	}
}

char	*read_command_line(void)
{
	char	*input;
	char	*trim;

	input = readline("minishell$ ");
	if (input)
		add_history(input);
	trim = ft_strtrim(input, " \t");
	free(input);
	if (!has_finished_quotes(trim))
	{
		input = finish_quotes(trim);
		free(trim);
		trim = ft_strtrim(input, "\n");
		free(input);
	}
	return (trim);
}

void	run_minishell(t_data *data)
{
	while (data)
	{
		free_minishell(data);
		config_minishell_signals(&data->saved_termios);
		data->input = read_command_line();
		if (g_signal == MINI_SIGINT)
			g_signal = NO_SIGNAL;
		if (!data->input || word_match(data->input, "exit"))
		{
			printf("exit\n");
			break ;
		}
		if (word_match(data->input, "history -c"))
			rl_clear_history();
		tokenize(data);
		parse(data);
		execute(data);
	}
}

int	main(void)
{
	t_data	*data;

	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("minishell: not a terminal", STDERR_FILENO);
		return (1);
	}
	data = initialize_minishell();
	run_minishell(data);
	ft_str_arr_free(&data->env);
	free_minishell(data);
	free(data);
	return (0);
}
