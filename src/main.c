/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/14 17:46:33 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

/*
	TODO LIST:

	- Signals
	- Move Command not found to executor so it runs each one if pipes
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
		cleanup_minishell(data);
		initalize_signals();
		data->input = readline(SHELL_PROMPT);
		if (!data->input)
			exit_minishell(data, EXIT_SUCCESS);
		if (data->input[0] != '\0')
			add_history(data->input);
		if (ft_strlen(data->input) != 0
			&& input_matches(data->input, "history -c"))
		{
			rl_clear_history();
			continue ;
		}
		data->toks = tokenizer(data);
		data->job = parser(data);
		executor(data);
	}
	exit_minishell(data, EXIT_SUCCESS);
}
