/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 10:10:23 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

t_data	*init_data(char **environ)
{
	t_data	*d;

	d = malloc(sizeof(t_data));
	if (!d)
		return (NULL);
	d->input = NULL;
	d->cmd_ct = 0;
	d->env = ft_str_arr_dup((const char **)environ);
	if (!d->env)
	{
		free(d);
		return (NULL);
	}
	d->exit_stat = 0;
	d->r_input_fd = 0;
	d->r_output_fd = 1;
	d->prev_pipefd[0] = -1;
	d->prev_pipefd[1] = -1;
	d->toks = NULL;
	d->job = NULL;
	return (d);
}

void	free_data(t_data *d)
{
	ft_free_str_arr(&d->env);
	free(d);
}
