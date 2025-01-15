/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/15 13:02:45 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Initialize the data struct
*
* @return The data struct
*/
t_data	*init_data(void)
{
	extern char	**environ;
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = ft_str_arr_dup((const char **)environ);
	if (!data->env)
	{
		free(data);
		return (NULL);
	}
	data->input = NULL;
	data->exit_stat = 0;
	data->r_input_fd = -1;
	data->r_output_fd = -1;
	data->toks = NULL;
	data->job = NULL;
	// data->prev_pipe_fd[0] = -1;
	// data->prev_pipe_fd[1] = -1;
	data->save_stdout = -1;
	data->save_stdin = -1;
	data->first_cmd = true;
	data->cmd_ct = 0;
	return (data);
}
