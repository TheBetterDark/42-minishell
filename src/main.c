/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/13 14:07:17 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

/*
	TODO LIST:

	- Signals
	- Move Command not found to executor so it runs each one if piped
	- Fix issues with pipes (cat | cat | ls)
	- fix pipe (only pipes the first command into the second one)
*/

/*
* @brief The main entry point of the shell
*
* @return int EXIT_SUCCESS on success, EXIT_FAILURE on error
*/
int	main(void)
{
	t_data		*data;

	data = init_data();
	while (true)
	{
		if (initalize_signals() == -1)
			handle_error(data, NULL, EXIT_FAILURE, true);
		data->input = readline(SHELL_PROMPT);
		if (!data->input)
			handle_error(data, ERR_UNKNOWN, EXIT_FAILURE, false);
		if (data->input[0] != '\0')
			add_history(data->input);
		if (input_matches(data->input, "history -c"))
		{
			rl_clear_history();
			cleanup_minishell(data);
			continue ;
		}
		data->toks = tokenizer(data);
		data->job = parser(data);
		executor(data);
		cleanup_minishell(data);
	}
	exit_minishell(data, EXIT_SUCCESS);
}
