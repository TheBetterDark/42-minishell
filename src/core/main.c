/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:54:22 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/27 20:55:55 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*display_prompt(t_data *data);

int	main(void)
{
	t_data	*data;

	data = initialize_shell();
	if (!data)
		return (EXIT_FAILURE);
	if (initalize_signals() == -1)
		return (free(data), EXIT_FAILURE);
	while (true)
	{
		data->input = display_prompt(data);
		if (!data->input)
			break ;
		free(data->input);
	}
	free(data);
	printf("exit\n");
	return (EXIT_SUCCESS);
}

static char	*display_prompt(t_data *data)
{
	char	prompt_str[256];
	char	*input;

	ft_snprintf(prompt_str, sizeof(prompt_str),
		USR "%s@%s" RST ":" CWD "%s" RST "$ ", data->user,
		data->hostname, data->cwd);
	input = readline((const char *)prompt_str);
	return (input);
}
