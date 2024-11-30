/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:54:22 by muabdi            #+#    #+#             */
/*   Updated: 2024/11/30 15:58:39 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*display_prompt(t_data *data);
static void	main_loop(t_data *data);

/*
* @brief The main entry point of the shell
*
* @return int EXIT_SUCCESS on success, EXIT_FAILURE on error
*/
int	main(void)
{
	t_data	*data;

	data = initialize_shell();
	if (!data)
		return (EXIT_FAILURE);
	if (initalize_signals() == -1)
		return (free(data), EXIT_FAILURE);
	main_loop(data);
	free(data);
	printf("exit\n");
	return (EXIT_SUCCESS);
}

static void	main_loop(t_data *data)
{
	static t_token	*current_token = NULL;
	t_token			*tokens;

	while (true)
	{
		data->input = display_prompt(data);
		if (!data->input || ft_strncmp(data->input, "exit", 5) == 0)
			break ;
		printf("Input: %s\n", data->input);
		tokens = lexer_tokenize(data->input);
		if (!tokens)
		{
			printf("No tokens generated.\n");
			continue ;
		}
		current_token = tokens;
		while (current_token != NULL)
		{
			printf("Token Type: %d, Token Value: %s\n", current_token->type,
				current_token->value);
			current_token = current_token->next;
		}
		token_cleanup(&tokens);
		free(data->input);
	}
}

/*
* @brief Display the shell prompt
*
* @param data The shell data structure
* @return char* The user input
*/
static char	*display_prompt(t_data *data)
{
	char	prompt_str[256];
	char	*input;

	ft_snprintf(prompt_str, sizeof(prompt_str),
		USR "%s@%s" RST ":" CWD "%s" RST "$ ", data->user, data->hostname,
		data->cwd);
	input = readline((const char *)prompt_str);
	return (input);
}
