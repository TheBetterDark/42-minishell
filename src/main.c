/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/22 17:36:11 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

/*
	TODO LIST:

	- Signals (Needs to Ctrl + C all when there are multiple heredoc
		commands chained)
	- Heredoc ENV Expansions (Double Quotes & restore tabs and spaces)
	- Has to work with NULL cmdv
	- Adjust redirect_files to traverse each cmd->ins & cmd->outs
*/

/*
* @brief The main entry point of the shell
*
* @return int EXIT_SUCCESS on success, EXIT_FAILURE on error
*/
int	main(void)
{
	t_data	*data;

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
