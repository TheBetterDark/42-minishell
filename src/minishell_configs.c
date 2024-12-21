/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_configs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/21 21:28:27 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	readline_config(t_data *d)
{
	add_history(d->input);
	if (input_matches(d->input, "history -c"))
		rl_clear_history();
	else if (input_matches(d->input, "exit"))
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}
