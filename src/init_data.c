/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/16 17:11:45 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

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
	d->input_fd = 0;
	d->output_fd = 1;
	d->r_input_fd = -1;
	d->r_output_fd = -1;
	return (d);
}
