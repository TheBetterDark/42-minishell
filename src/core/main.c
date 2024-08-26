/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:54:22 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/26 15:57:37 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(void)
{
	t_prompt	*prompt;
	char		*buffer;

	prompt = initialize_prompt();
	if (!prompt)
		return (EXIT_FAILURE);
	while (true)
	{
		buffer = display_prompt(prompt);
		if (!buffer)
			break ;
		if (ft_strncmp(buffer, "exit", 4) == 0)
		{
			printf("exit\n");
			free(buffer);
			break ;
		}
		free(buffer);
	}
	free(prompt);
	return (EXIT_SUCCESS);
}
