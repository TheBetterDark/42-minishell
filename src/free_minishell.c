/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/18 18:38:52 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	free_job(t_cmd *job)
{
	t_cmd	*cur;
	t_cmd	*save;

	cur = job;
	while (cur != NULL)
	{
		save = cur->next;
		ft_free_str_arr(cur->cmdv);
		free(cur->eof);
		free(cur->open_fn);
		free(cur->append_fn);
		free(cur->input_fn);
		free(cur);
		cur = save;
	}
}

void	free_minishell(t_data *d)
{
	free(d->input);
	d->cmd_ct = 0;
	tok_lstclear(&d->toks);
	free(d->job);
	d->input_fd = 0;
	d->output_fd = 1;
	d->r_input_fd = -1;
	d->r_output_fd = -1;
}
